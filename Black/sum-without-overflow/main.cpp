#include <iostream>
#include <limits>

using namespace std;


bool func(int64_t a, int64_t b) {
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        return true;
    } else if (a < 0 && b < 0) {
        return (INT64_MIN - a) <= b;
    }
    return (INT64_MAX - a) >= b;
}

int main() {
    int64_t a = 0;
    int64_t b = 0;

    cin >> a >> b;

    cout << (func(a, b) ? to_string(a + b) : "Overflow!");


    return 0;
}
