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
        return to_string(value);
    }

private:
    int value;
};

class SumExpr : public Expression {
public:
    explicit SumExpr(ExpressionPtr new_left, ExpressionPtr new_right)
            : left(move(new_left)), right(move(new_right)) {}

    int Evaluate() const override {
        return left->Evaluate() + right->Evaluate();
    }

    string ToString() const override {
        return "("s + left->ToString() + ")"s + "+"s + "("s + right->ToString() + ")"s;
    }

private:
    ExpressionPtr left, right;
};

class ProductExpr : public Expression {
public:
    explicit ProductExpr(ExpressionPtr new_left, ExpressionPtr new_right)
            : left(move(new_left)), right(move(new_right)) {}

    int Evaluate() const override {
        return left->Evaluate() * right->Evaluate();
    }

    string ToString() const override {
        return "("s + left->ToString() + ")"s + "*"s + "("s + right->ToString() + ")"s;
    }

private:
    ExpressionPtr left, right;
};


ExpressionPtr Value(int value) {
    return make_unique<ValueExpr>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<SumExpr>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<ProductExpr>(move(left), move(right));
}


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