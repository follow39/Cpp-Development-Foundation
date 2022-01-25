#include "lexer.h"

#include <algorithm>
#include <charconv>
#include <unordered_map>

using namespace std;

namespace Parse {

    bool operator==(const Token &lhs, const Token &rhs) {
        using namespace TokenType;

        if (lhs.index() != rhs.index()) {
            return false;
        }
        if (lhs.Is<Char>()) {
            return lhs.As<Char>().value == rhs.As<Char>().value;
        } else if (lhs.Is<Number>()) {
            return lhs.As<Number>().value == rhs.As<Number>().value;
        } else if (lhs.Is<String>()) {
            return lhs.As<String>().value == rhs.As<String>().value;
        } else if (lhs.Is<Id>()) {
            return lhs.As<Id>().value == rhs.As<Id>().value;
        } else {
            return true;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Token &rhs) {
        using namespace TokenType;

#define VALUED_OUTPUT(type) \
  if (auto p = rhs.TryAs<type>()) return os << #type << '{' << p->value << '}';

        VALUED_OUTPUT(Number);
        VALUED_OUTPUT(Id);
        VALUED_OUTPUT(String);
        VALUED_OUTPUT(Char);

#undef VALUED_OUTPUT

#define UNVALUED_OUTPUT(type) \
    if (rhs.Is<type>()) return os << #type;

        UNVALUED_OUTPUT(Class);
        UNVALUED_OUTPUT(Return);
        UNVALUED_OUTPUT(If);
        UNVALUED_OUTPUT(Else);
        UNVALUED_OUTPUT(Def);
        UNVALUED_OUTPUT(Newline);
        UNVALUED_OUTPUT(Print);
        UNVALUED_OUTPUT(Indent);
        UNVALUED_OUTPUT(Dedent);
        UNVALUED_OUTPUT(And);
        UNVALUED_OUTPUT(Or);
        UNVALUED_OUTPUT(Not);
        UNVALUED_OUTPUT(Eq);
        UNVALUED_OUTPUT(NotEq);
        UNVALUED_OUTPUT(LessOrEq);
        UNVALUED_OUTPUT(GreaterOrEq);
        UNVALUED_OUTPUT(None);
        UNVALUED_OUTPUT(True);
        UNVALUED_OUTPUT(False);
        UNVALUED_OUTPUT(Eof);

#undef UNVALUED_OUTPUT

        return os << "Unknown token :(";
    }

    Lexer::Lexer(std::istream &new_input)
            : input(new_input) {
        input >> ws;

        NextToken();
    }

    const Token &Lexer::CurrentToken() const {
        return currentToken;
    }

    Token Lexer::NextToken() {
        if (!currentToken.Is<TokenType::Eof>()) {
            Token nextToken;
            if (currentToken.Is<TokenType::Indent>() && input.peek() == ' ') {
                input.get();
                input.get();
                currentIndent += incIndent;
                nextToken = Token{TokenType::Indent{}};
            } else if (currentToken.Is<TokenType::Dedent>()) {
                if (currentIndent > futureIndent) {
                    currentIndent -= incIndent;
                    nextToken = Token{TokenType::Dedent{}};
                } else if (input.peek() == '\n') {
                    input.get();
                    nextToken = NextToken();
                }
            } else if (currentToken.Is<TokenType::Newline>()) {
                int cnt = 0;
                while (input.peek() == ' ' && cnt != currentIndent) {
                    input.get();
                    ++cnt;
                }
                if (input.peek() == '\n') {
                    input.get();
                    nextToken = NextToken();
                } else if (cnt < currentIndent) {
                    futureIndent = cnt;
                    currentIndent -= incIndent;
                    nextToken = Token{TokenType::Dedent{}};
                } else if (cnt == currentIndent && input.peek() == ' ') {
                    input.get();
                    input.get();
                    currentIndent += incIndent;
                    nextToken = Token{TokenType::Indent{}};
                }
            }
            if (nextToken.Is<std::monostate>()) {
                while (input.peek() == ' ') {
                    input.get();
                }

                if (isdigit(input.peek())) {
                    nextToken = ParseNumber(input);
                } else if (input.peek() == '\'' || input.peek() == '\"') {
                    nextToken = ParseString(input);
                } else if (isalpha(input.peek()) || input.peek() == '_') {
                    nextToken = ParseWord(input);
                } else {
                    nextToken = ParseChar(input);
                    if (nextToken.Is<TokenType::Eof>() && !currentToken.Is<TokenType::Newline>()) {
                        nextToken = Token{TokenType::Newline{}};
                    }
                }
            }

            currentToken = nextToken;
        }

        return currentToken;
    }

    Token Lexer::ParseNumber(istream &input) {
        int value = 0;
        input >> value;
        return Token(TokenType::Number{value});
    }

    Token Lexer::ParseWord(istream &input) {
        const std::unordered_map<std::string, Token> keywords = {
                {"class",  Token{TokenType::Class{}}},
                {"return", Token{TokenType::Return{}}},
                {"if",     Token{TokenType::If{}}},
                {"else",   Token{TokenType::Else{}}},
                {"def",    Token{TokenType::Def{}}},
                {"print",  Token{TokenType::Print{}}},
                {"or",     Token{TokenType::Or{}}},
                {"and",    Token{TokenType::And{}}},
                {"not",    Token{TokenType::Not{}}},
                {"True",   Token{TokenType::True{}}},
                {"False",  Token{TokenType::False{}}},
                {"None",   Token{TokenType::None{}}},
//                "class", "return", "if", "else", "def", "print", "or", "and", "not", "True", "False", "None"
        };

        Token result;
        string value;

        do {
            char temp;
            input.get(temp);
            value += temp;
        } while (input && (isalpha(input.peek()) ||
                           isdigit(input.peek()) ||
                           input.peek() == '_'));

        if (keywords.find(value) != keywords.end()) {
            result = keywords.at(value);
        } else {
            result = Token{TokenType::Id{value}};
        }

        return result;
    }

    Token Lexer::ParseChar(istream &input) {
        char ch;
        input.get(ch);

        switch (ch) {
            case '=':
                if (input.peek() == '=') {
                    input.get();
                    return Token(TokenType::Eq{});
                }
                return Token(TokenType::Char{'='});
            case '>':
                if (input.peek() == '=') {
                    input.get();
                    return Token(TokenType::GreaterOrEq{});
                }
                return Token(TokenType::Char{'>'});
            case '<':
                if (input.peek() == '=') {
                    input.get();
                    return Token(TokenType::LessOrEq{});
                }
                return Token(TokenType::Char{'<'});
            case '!':
                if (input.peek() == '=') {
                    input.get();
                    return Token(TokenType::NotEq{});
                }
                break;
            case '\n':
                return Token(TokenType::Newline{});
            case '\0':
            case EOF:
                return Token(TokenType::Eof{});
            default:
                break;
        }

        return Token{TokenType::Char{ch}};
    }

    Token Lexer::ParseString(istream &input) {
        char limiter;
        input.get(limiter);
        string value;

        do {
            char temp;
            input.get(temp);
            value += temp;
        } while (input && input.peek() != limiter);
        input.get(limiter);

        return Token(TokenType::String{value});
    }


} /* namespace Parse */