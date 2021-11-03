#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>
#include <mutex>

using namespace std;

class InvertedIndex {
public:
    InvertedIndex& operator=(InvertedIndex &&other)  noexcept;

    void Add(const string& document);

    map<size_t, size_t> Lookup(const string &word);

    const string &GetDocument(size_t id) const {
        return docs[id];
    }

private:
    map<string, pair<mutex, map<size_t, size_t>>> index;

    vector<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    InvertedIndex index;
};
