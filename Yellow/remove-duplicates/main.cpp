#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& vec) {
    for(const auto& v : vec) {
        os << v << ' ';
    }
    return os;
}

void GenerateString(vector<int>& vec, int n) {
    while(n-- > 0) {
        vec.push_back(n);
    }
}

void PrintPermutation(int n) {
    vector<int> vec;
    GenerateString(vec, n);
    std::sort(vec.rbegin(), vec.rend());
    do {
        std::cout << vec << '\n';
    } while(std::prev_permutation(vec.begin(), vec.end()));
}

int main() {
    int n = 0;
    cin >> n;

    PrintPermutation(n);

    return 0;
}
