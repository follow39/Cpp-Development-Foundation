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

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end)
        , size_(distance(first, last))
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator {
private:
    vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (size_t left = distance(begin, end); left > 0; ) {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for(const auto& [key, value] : other.word_frequences) {
            word_frequences[key] += value;
        }
    }
};

template <typename ContainerOfVectors>
Stats ExploreKeyWordsSingleThread(const set<string>& key_words, const ContainerOfVectors& words) {
    Stats result;
    for(const auto& word : words) {
        if(key_words.count(word) != 0) {
            ++result.word_frequences[word];
        }
    }
//    for(const auto& word : key_words) {
//        size_t cnt = count(words.begin(), words.end(), word);
//        if(cnt) {
//            result.word_frequences[word] = cnt;
//        }
//    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> futures;
//    futures.reserve(key_words.size());
    vector<string> words;
//    words.reserve(key_words.size());
    Stats result;

    while(input) {
        string temp;
        input >> temp;
        if(!temp.empty()) {
            words.push_back(temp);
        }
    }

    const auto pages = Paginate(words, words.size()/8);
//    futures.reserve(pages.size());
    for(const auto& page : pages) {
        futures.push_back(async([=] { return ExploreKeyWordsSingleThread(key_words, page); }));
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
//    LOG_DURATION("Total");
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
