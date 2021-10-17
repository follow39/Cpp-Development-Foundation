#include <iostream>
#include <sstream>

#include "date.h"
#include "budget.h"

using namespace std;



int main()
{
    Budget budget;
    string cmd;
    string from;
    string to;

    int q = 0;
    cin >> q;
    cout.precision(25);
    while(q-- > 0) {
        cin >> cmd;
        if(cmd == "ComputeIncome") {
            cin >> from >> to;
            cout << fixed << budget.ComputeIncome(DateFromString(from), DateFromString(to)) << endl;
        }
        if(cmd == "Earn") {
            int value = 0;
            cin >> from >> to >> value;
            budget.AddIncome(DateFromString(from), DateFromString(to), value);
        }
    }

    return 0;
}
