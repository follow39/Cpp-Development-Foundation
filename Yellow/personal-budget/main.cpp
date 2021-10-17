#include <iostream>
#include <sstream>

#include "budget.h"
#include "date.h"

using namespace std;

Date DateFromString(const string& date) {
    stringstream ss(date);
    int year = 0;
    int month = 0;
    int day = 0;
    char ch1 = 0;
    char ch2 = 0;

    ss >> year >> ch1 >> month >> ch2 >> day;

    return {year, month, day};
}

int main()
{
    Budget budget;
    string cmd;
    string from;
    string to;

    int q = 0;
    cin >> q;
    while(q-- > 0) {
        cin >> cmd;
        if(cmd == "ComputeIncome") {
            cin >> from >> to;
            cout << budget.ComputeIncome(DateFromString(from), DateFromString(to)) << endl;
        }
        if(cmd == "Earn") {
            int value = 0;
            cin >> from >> to >> value;
            budget.AddIncome(DateFromString(from), DateFromString(to), value);
        }
    }

    return 0;
}
