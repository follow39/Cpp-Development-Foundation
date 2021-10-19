#include <iostream>
#include <string>

using namespace std;

class ArithmeticExpression {
public:
    ArithmeticExpression(int x)
    {
        expression += '(';
        expression += to_string(x);
        expression += ')';
    }
    void AddExpression(char op, int value) {
        expression.insert(expression.begin(), '(');
        expression += ' ';
        expression += op;
        expression += ' ';
        expression += to_string(value);
        expression += ')';
    }
    string GetExpressionString() const {
        return expression;
    }
private:
    string expression;
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
