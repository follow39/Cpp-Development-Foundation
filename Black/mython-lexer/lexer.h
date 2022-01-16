#pragma once

#include <iosfwd>
#include <string>
#include <sstream>
#include <variant>
#include <stdexcept>
#include <optional>
#include <unordered_map>
#include <vector>

class TestRunner;

namespace Parse {

    namespace TokenType {
        struct Number {
            int value;
        };

        struct Id {
            std::string value;
        };

        struct Char {
            char value;
        };

        struct String {
            std::string value;
        };

        struct Class {
        };
        struct Return {
        };
        struct If {
        };
        struct Else {
        };
        struct Def {
        };
        struct Newline {
        };
        struct Print {
        };
        struct Indent {
        };
        struct Dedent {
        };
        struct Eof {
        };
        struct And {
        };
        struct Or {
        };
        struct Not {
        };
        struct Eq {
        };
        struct NotEq {
        };
        struct LessOrEq {
        };
        struct GreaterOrEq {
        };
        struct None {
        };
        struct True {
        };
        struct False {
        };
    }

    using TokenBase = std::variant<
            std::monostate,
            TokenType::Number,
            TokenType::Id,
            TokenType::Char,
            TokenType::String,
            TokenType::Class,
            TokenType::Return,
            TokenType::If,
            TokenType::Else,
            TokenType::Def,
            TokenType::Newline,
            TokenType::Print,
            TokenType::Indent,
            TokenType::Dedent,
            TokenType::And,
            TokenType::Or,
            TokenType::Not,
            TokenType::Eq,
            TokenType::NotEq,
            TokenType::LessOrEq,
            TokenType::GreaterOrEq,
            TokenType::None,
            TokenType::True,
            TokenType::False,
            TokenType::Eof
    >;


//По сравнению с условием задачи мы добавили в тип Token несколько
//удобных методов, которые делают код короче. Например,
//
//token.Is<TokenType::Id>()
//
//гораздо короче, чем
//
//std::holds_alternative<TokenType::Id>(token).
    struct Token : TokenBase {
        using TokenBase::TokenBase;

        template<typename T>
        [[nodiscard]] bool Is() const {
            return std::holds_alternative<T>(*this);
        }

        template<typename T>
        const T &As() const {
            return std::get<T>(*this);
        }

        template<typename T>
        const T *TryAs() const {
            return std::get_if<T>(this);
        }
    };

    bool operator==(const Token &lhs, const Token &rhs);

    std::ostream &operator<<(std::ostream &os, const Token &rhs);

    class LexerError : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };

    class Lexer {
    public:
        using Tokens = std::vector<Token>;

    public:
        explicit Lexer(std::istream &input);

        [[nodiscard]] const Token &CurrentToken() const;

        Token NextToken();

        template<typename T>
        const T &Expect() const {
            if (!currentToken->Is<T>()) {
                throw LexerError{"Current type is not equal to expected"};
            }
            return *currentToken->TryAs<T>();
        }

        template<typename T, typename U>
        void Expect(const U &value) const {
            Expect<T>();
            if (currentToken->As<T>().value != value) {
                throw LexerError{"Current value is not equal to expected"};
            }
        }

        template<typename T>
        const T &ExpectNext() {
            NextToken();
            return Expect<T>();
        }

        template<typename T, typename U>
        void ExpectNext(const U &value) {
            NextToken();
            Expect<T>(value);
        }

    private:
        static Token ParseNumber(std::istream &input);

        static Token ParseWord(std::istream &input);

        static Token ParseChar(std::istream &input);

        static Token ParseString(std::istream &input);

        Tokens tokens;
        Tokens::iterator currentToken;
    };

    void RunLexerTests(TestRunner &test_runner);

} /* namespace Parse */
