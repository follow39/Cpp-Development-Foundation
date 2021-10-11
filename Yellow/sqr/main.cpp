#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <class T> T Sqr(const T& x);
template <class First, class Second> pair<First, Second> Sqr(const pair<First, Second>& x);
template <class T> vector<T> Sqr(const vector<T>& x);
template <class Key, class Value> map<Key, Value> Sqr(const map<Key, Value>& x);

template <class T>
T Sqr(const T& x) {
    return x * x;
}

template <class First, class Second>
pair<First, Second> Sqr(const pair<First, Second>& x) {
    return {Sqr(x.first), Sqr(x.second)};
}

template <class T>
vector<T> Sqr(const vector<T>& x) {
    vector<T> result;
    for(const auto& i : x) {
        result.push_back(Sqr(i));
    }
    return result;
}

template <class Key, class Value>
map<Key, Value> Sqr(const map<Key, Value>& x) {
    map<Key, Value> result;
    for(const auto& [key, value] : x) {
        result[key] = Sqr(value);
    }
    return result;
}

int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}
