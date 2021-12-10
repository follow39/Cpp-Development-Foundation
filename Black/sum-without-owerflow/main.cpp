#include <iostream>
#include <limits>

using namespace std;

int main() {
    int64_t a = 0;
    int64_t b = 0;

    cin >> a >> b;

    cout << (((INT64_MAX - a) > b) ? to_string(a + b) : "Owerflow!") << endl;


    return 0;
}
