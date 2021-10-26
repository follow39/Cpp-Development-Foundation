#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <iterator>
#include "test_runner.h"
#include "profile.h"

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        size_t temp_size = dict.size();
        copy(words.begin(), words.end(), inserter(dict, dict.end()));
        return static_cast<int>(dict.size() - temp_size);
    }

    vector<string> KnownWords() {
        return vector<string>{dict.begin(), dict.end()};
    }
};


int main() {
    LOG_DURATION("Total");
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }

    return 0;
}
