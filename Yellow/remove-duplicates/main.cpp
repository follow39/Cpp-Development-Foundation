#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& vec) {
    for(const auto& v : vec) {
        os << v << ' ';
    }
    return os;
}

void PrintPermutation(int n) {
    vector<int> vec(n);
    iota(vec.rbegin(), vec.rend(), 1);
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
