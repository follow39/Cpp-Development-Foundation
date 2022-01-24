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

    Lexer::Lexer(std::istream &input) {
        input >> ws;

        int currentIndent = 0;

        while (input) {
            if (!tokens.empty() && tokens.back().Is<TokenType::Newline>()) {
                int cnt = 0;
                while (input.peek() == ' ') {
                    input.get();
                    ++cnt;
                }
                if (input.peek() == '\n') {
                    input.get();
                    continue;
                }
                if (cnt > currentIndent) {
                    tokens.push_back(Token(TokenType::Indent{}));
                    currentIndent = cnt;
                    continue;
                } else if (cnt < currentIndent) {
                    const int incIndent = 2;
                    for (; currentIndent > cnt; currentIndent -= incIndent) {
                        tokens.push_back(Token(TokenType::Dedent{}));
                    }
                    continue;
                }
            }

            while (input.peek() == ' ') {
                input.get();
            }

            if (isdigit(input.peek())) {
                tokens.push_back(ParseNumber(input));
                continue;
            } else if (input.peek() == '\'' || input.peek() == '\"') {
                tokens.push_back(ParseString(input));
                continue;
            } else if (isalpha(input.peek()) || input.peek() == '_') {
                tokens.push_back(ParseWord(input));
                continue;
            } else {
                tokens.push_back(ParseChar(input));
                continue;
            }
        }

        if (!tokens.empty() && tokens.back().Is<TokenType::Eof>()) {
            tokens.pop_back();
        }
        if (tokens.empty() || (!tokens.back().Is<TokenType::Newline>() && !tokens.back().Is<TokenType::Dedent>())) {
            tokens.push_back(Token{TokenType::Newline{}});
        }
        tokens.push_back(Token{TokenType::Eof{}});

        currentToken = tokens.begin();
    }

    const Token &Lexer::CurrentToken() const {
        if (currentToken == tokens.end()) {
            return tokens.back();
        }
        return *currentToken;
    }

    Token Lexer::NextToken() {
        if (currentToken == tokens.end()) {
            return tokens.back();
        }
        ++currentToken;
        return CurrentToken();
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
            default:
                break;
        }

        switch (ch) {
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