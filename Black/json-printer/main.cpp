#include "test_runner.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <variant>
#include <map>
#include <iomanip>

using namespace std;

void PrintJsonString(std::ostream &out, std::string_view str);

void PrintJsonStringNull(std::ostream &out);

namespace Json {

    template<typename Base>
    class Array;

    template<typename Base>
    class Object;

    template<typename Base>
    class ObjectValue;

    class Empty;


    template<typename Base>
    class Array {
    public:
        explicit Array(ostream &new_out, Base *new_base = nullptr)
                : out(new_out), base(new_base) {
            out << '[';
        }

        Array &Null() {
            PrintDelimiter();
            PrintJsonStringNull(out);
            return *this;
        }

        Array &String(const string &input) {
            PrintDelimiter();
            PrintJsonString(out, input);
            return *this;
        }

        Array &Number(int64_t input) {
            PrintDelimiter();
            out << input;
            return *this;
        }

        Array &Boolean(bool input) {
            PrintDelimiter();
            out << std::boolalpha << input;
            return *this;
        }

        Object<Array<Base>> BeginObject() {
            PrintDelimiter();
            return Object{out, this};
        }

        Array<Array<Base>> BeginArray() {
            PrintDelimiter();
            return Array<Array<Base>>{out, this};
        }

        Base &EndArray() {
            if (!ended) {
                out << ']';
                ended = true;
            }
            return *base;
        }

        ~Array() {
            EndArray();
        }

    private:
        void PrintDelimiter() {
            if (!empty) {
                out << ',';
            }
            empty = false;
        }

        ostream &out;
        Base *base;
        bool empty = true;
        bool ended = false;
    };

    template<typename Base>
    class Object {
    public:
        explicit Object(ostream &new_out, Base *new_base = nullptr)
                : out(new_out), base(new_base) {
            out << '{';
        }

        ObjectValue<Object<Base>> Key(const string &key) {
            PrintDelimiter();
            PrintJsonString(out, key);
            out << ':';
            return ObjectValue(out, this);
        }

        Base &EndObject() {
            if (!ended) {
                out << '}';
                ended = true;
            }
            return *base;
        }

        ~Object() {
            EndObject();
        }

    private:
        void PrintDelimiter() {
            if (!empty) {
                out << ',';
            }
            empty = false;
        }

        ostream &out;
        Base *base;
        bool empty = true;
        bool ended = false;
    };

    template<typename Base>
    class ObjectValue {
    public:
        explicit ObjectValue(ostream &new_out, Base *new_base = nullptr)
                : out(new_out), base(new_base) {}

        Array<Base> BeginArray() {
            used = true;
            return Array(out, base);
        }

        Object<Base> BeginObject() {
            used = true;
            return Object(out, base);
        }

        Base &Null() {
            used = true;
            PrintJsonStringNull(out);
            return *base;
        }

        Base &String(const string &input) {
            used = true;
            PrintJsonString(out, input);
            return *base;
        }

        Base &Number(int64_t input) {
            used = true;
            out << input;
            return *base;
        }

        Base &Boolean(bool input) {
            used = true;
            out << std::boolalpha << input;
            return *base;
        }

        ~ObjectValue() {
            EndObjectValue();
        }

    private:
        void EndObjectValue() {
            if (!used) {
                Null();
            }
        }

        ostream &out;
        Base *base;
        bool used = false;
    };

    class Empty {
    public:
        explicit Empty(ostream &new_out)
                : out(new_out) {}

    private:
        ostream &out;
    };

}


void PrintJsonString(std::ostream &out, std::string_view str) {
    out << '\"';
    for (const char s: str) {
        if (s == '\\' || s == '\"') {
            out << '\\';
        }
        out << s;
    }
    out << '\"';
}

void PrintJsonStringNull(std::ostream &out) {
    out << "null";
}

using ArrayContext = Json::Array<Json::Empty>;  // Замените это объявление на определение типа ArrayContext
ArrayContext PrintJsonArray(std::ostream &out) {
    // реализуйте функцию
    return ArrayContext{out};
}

using ObjectContext = Json::Object<Json::Empty>;  // Замените это объявление на определение типа ObjectContext
ObjectContext PrintJsonObject(std::ostream &out) {
    // реализуйте функцию
    return ObjectContext{out};
}

void TestArray() {
    std::ostringstream output;

    {
        auto json = PrintJsonArray(output);
        json
                .Number(5)
                .Number(6)
                .BeginArray()
                .Number(7)
                .EndArray()
                .Number(8)
                .String("bingo!");
    }

    ASSERT_EQUAL(output.str(), R"([5,6,[7],8,"bingo!"])");
}

void TestObject() {
    std::ostringstream output;

    {
        auto json = PrintJsonObject(output);
        json
                .Key("id1").Number(1234)
                .Key("id2").Boolean(false)
                .Key("").Null()
                .Key("\"").String("\\");
    }

    ASSERT_EQUAL(output.str(), R"({"id1":1234,"id2":false,"":null,"\"":"\\"})");
}

void TestAutoClose() {
    std::ostringstream output;

    {
        auto json = PrintJsonArray(output);
        json.BeginArray().BeginObject();
    }

    ASSERT_EQUAL(output.str(), R"([[{}]])");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestArray);
    RUN_TEST(tr, TestObject);
    RUN_TEST(tr, TestAutoClose);


    PrintJsonString(std::cout, "Hello, \"world\"");
// "Hello, \"world\""

    PrintJsonArray(std::cout)
            .Null()
            .String("Hello")
            .Number(123)
            .Boolean(false)
            .EndArray();  // явное завершение массива
// [null,"Hello",123,false]

    PrintJsonArray(std::cout)
            .Null()
            .String("Hello")
            .Number(123)
            .Boolean(false);
// [null,"Hello",123,false]

    PrintJsonArray(std::cout)
            .String("Hello")
            .BeginArray()
            .String("World");
// ["Hello",["World"]]

    PrintJsonObject(std::cout)
            .Key("foo")
            .BeginArray()
            .String("Hello")
            .EndArray()
            .Key("foo")  // повторяющиеся ключи допускаются
            .BeginObject()
            .Key("foo");  // закрытие объекта в таком состоянии допишет null в качестве значения
// {"foo":["Hello"],"foo":{"foo":null}}

/*
    PrintJsonObject(std::cout)
            .String("foo");  // ошибка компиляции

    PrintJsonObject(std::cout)
            .Key("foo")
            .Key("bar");  // ошибка компиляции

    PrintJsonObject(std::cout)
            .EndArray();  // ошибка компиляции

    PrintJsonArray(std::cout)
            .Key("foo")
            .BeginArray()
            .EndArray()
            .EndArray();  // ошибка компиляции

    PrintJsonArray(std::cout)
            .EndArray()
            .BeginArray();  // ошибка компиляции  (JSON допускает только одно верхнеуровневое значение)

    PrintJsonObject(std::cout)
            .EndObject()
            .BeginObject();  // ошибка компиляции  (JSON допускает только одно верхнеуровневое значение)
*/

    return 0;
}
