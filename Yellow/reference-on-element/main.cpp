#include <iostream>
#include <map>

using namespace std;

template <class Key, class Value>
Value& GetRefStrict(map<Key, Value>& input, Key key) {
    if(input.count(key) == 0) {
        throw runtime_error("");
    }
    return input[key];
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
    return 0;
}
