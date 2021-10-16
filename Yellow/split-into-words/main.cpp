#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto it = s.begin();
    auto temp = s.begin();

    while(it != s.end()) {
        temp = find(it, s.end(), ' ');
        result.push_back({it, temp});
        it = temp;
        if(it != s.end())
            ++it;
    }

    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
