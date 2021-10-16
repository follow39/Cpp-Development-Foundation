#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string GenerateString(int n) {
    if(n == 0)
        return "";
    else
        return to_string(n) + GenerateString(n-1);
}

void PrintPermutation(int n) {
    std::string s = GenerateString(n);
    std::sort(s.rbegin(), s.rend());
    do {
        std::cout << s << '\n';
    } while(std::prev_permutation(s.begin(), s.end()));
}

int main() {
    int n = 0;
    cin >> n;

    PrintPermutation(n);

    return 0;
}
