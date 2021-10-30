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

using namespace std;

template <typename Iterator>
class PaginatorPage {
public:
    PaginatorPage(Iterator begin, Iterator end, size_t size)
        : page_size(min(static_cast<size_t>(end - begin), size)),
          first(begin),
          last(begin + page_size) {}
    Iterator begin() {
        return first;
    }
    const Iterator begin() const {
        return first;
    }
    Iterator end() {
        return last;
    }
    const Iterator end() const {
        return last;
    }
    size_t size() const {
        return page_size;
    }

private:
    size_t page_size;
    Iterator first;
    Iterator last;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t size) {
        for(auto it = begin; it != end; it+=size) {
            pages.push_back({it, end, size});
            if(pages.back().size() < size) {
                break;
            }
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

private:
    vector<PaginatorPage<Iterator>> pages;
    size_t page_size;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{c.begin(), c.end(), page_size};
}

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
    stringstream ss(line);
    string word;
    while(ss >> word) {
        if(key_words.count(word)) {
            ++result.word_frequences[word];
        }
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> futures;
    Stats result;

    string temp;

    while(getline(input, temp)) {
        istringstream ss(temp);
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(ss)));
    }

    for(auto& x : futures) {
        result += x.get();
    }

    return result;
    //    return ExploreKeyWordsSingleThread(key_words, input);
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
