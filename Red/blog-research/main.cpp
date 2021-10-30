#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <future>
#include <functional>
#include <set>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for(const auto& [key, value] : other.word_frequences) {
            word_frequences[key] += value;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    string word;
    istringstream ss(line);
    while(ss >> word) {
        if(key_words.count(word)) {
            ++result.word_frequences[word];
        }
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, const string& input) {
    Stats result;
    istringstream ss(input);

    for(string line; getline(ss, line);) {
      result += ExploreLine(key_words, line);
    }
    return ExploreLine(key_words, input);
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> futures;
    Stats result;

    string temp;

    while(input) {
        temp.clear();
        for(int i = 0; i < 10 && input; ++i) {
            string line;
            getline(input, line);
            temp += line + ' ';
        }

        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(temp)));
    }

    for(auto& x : futures) {
        result += x.get();
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
