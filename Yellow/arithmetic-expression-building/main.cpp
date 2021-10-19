#include <iostream>
#include <string>

using namespace std;

class ArithmeticExpression {
public:
    ArithmeticExpression(const int x)
    {
        expression += to_string(x);
        prev_op = '*';
    }
    void AddExpression(const char op, const int value) {
        if((op == '*' || op == '/') && (prev_op != '*' && prev_op != '/')) {
            expression.insert(expression.begin(), '(');
            expression += ')';
        }
        expression += ' ';
        expression += op;
        expression += ' ';
        expression += to_string(value);
        prev_op = op;
    }
    string GetExpressionString() const {
        return expression;
    }
private:
    string expression;
    char prev_op;
};





int main()
{
    int x = 0;
    int n = 0;
    cin >> x >> n;

    ArithmeticExpression ae{x};

    char op = 0;
    int value = 0;
    while(n-- > 0) {
        cin >> op >> value;
        ae.AddExpression(op, value);
    }

    cout << ae.GetExpressionString() << endl;

    return 0;
}
