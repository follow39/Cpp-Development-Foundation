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


    template<class T>
    LexerError GenerateLexerError(T value) {
        string errorText = "Unknown token - ";
        errorText += to_string(value);
        return LexerError{errorText};
    }

    Lexer::Lexer(std::istream &new_input)
            : input(new_input), currentToken(NextToken()) {}

    const Token &Lexer::CurrentToken() const {
        return currentToken;
    }

    Token Lexer::NextToken() {
        Token result;

        if (currentToken.Is<TokenType::Newline>() && input.peek() == ' ') {
            int cnt = 0;
            while (input.peek() == ' ') {
                input.get();
                ++cnt;
            }
            if (cnt > currentIndent) {
                result = Token(TokenType::Indent{});
            } else if (cnt < currentIndent) {
                result = Token(TokenType::Dedent{});
            }
        } else {
            input >> ws;

            if (isdigit(input.peek())) {
                result = ParseNumber(input);
            } else if (input.peek() == '\'' || input.peek() == '\"') {
                result = ParseString(input);
            } else if (isalpha(input.peek()) || input.peek() == '_') {
                result = ParseWord(input);
            } else if (!isalpha(input.peek()) && !isdigit(input.peek()) &&
                       input.peek() != '\'' && input.peek() != '\"') {
                result = ParseChar(input);
            }
        }

        currentToken = result;
        return result;
    }

    Token Lexer::ParseNumber(istream &input) {
        int value = 0;
        input >> value;
        return Token(TokenType::Number{value});
    }

    Token Lexer::ParseWord(istream &input) {
        Token result;
        string value;

        do {
            char temp;
            input.get(temp);
            value += temp;
        } while (input && (isalpha(input.peek()) ||
                           isdigit(input.peek()) ||
                           input.peek() == '_'));
        switch (input.peek()) {
            case ' ':
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
            case '>':
            case '<':
            case '!':
            case ':':
            case ',':
            case '\n':
            case EOF:
                break;
            default:
                throw GenerateLexerError(input.peek());
        }

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
            case '+':
                return Token(TokenType::Char{'+'});
            case '-':
                return Token(TokenType::Char{'-'});
            case '*':
                return Token(TokenType::Char{'*'});
            case '/':
                return Token(TokenType::Char{'/'});
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
            case ':':
                return Token(TokenType::Char{':'});
            case ',':
                return Token(TokenType::Char{','});
            case '\n':
                return Token(TokenType::Newline{});
            case EOF:
                return Token(TokenType::Eof{});
            default:
                break;
        }

        throw GenerateLexerError(ch);

        return Token{};
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
        input.get();

        return Token(TokenType::String{value});
    }


} /* namespace Parse */