#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class ValueExpr : public Expression {
public:
    explicit ValueExpr(int new_value)
            : value(new_value) {}

    int Evaluate() const override {
        return value;
    }

    string ToString() const override {
        return "("s + to_string(value) + ")"s;
    }

private:
    int value;
};

class SumExpr : public Expression {
public:
    explicit SumExpr(ExpressionPtr new_left, ExpressionPtr new_right)
            : left(move(new_left)), right(move(new_right)) {}

    int Evaluate() const override {
//        return Sum(left->Evaluate(), right->Evaluate())->Evaluate;
        return 0; // !!!!!
    }

    string ToString() const override {
        return "("s + to_string(left->Evaluate()) + "+"s +
               to_string(right->Evaluate()) + ")"s;
    }

private:
    ExpressionPtr left, right;
};


string Print(const Expression *e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}