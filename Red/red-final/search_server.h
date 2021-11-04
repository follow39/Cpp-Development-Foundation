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
    void Add(string &document);

    const vector<pair<int, int>> &Lookup(const string &word) const;

private:
    map<string, vector<pair<int, int>>> index;
    int current_docid = 0;
    vector<pair<int, int>> empty_vector = {};
};

//struct Access {
//    lock_guard<mutex> guard;
//    InvertedIndex &ref_to_value;
//};

class SearchServer {
public:
    SearchServer() = default;

    void UpdateDocumentBase(istream &document_input);

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBaseThread(istream &document_input, int this_future_idx);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

    void AddQueriesThread(istream &query_input, ostream &search_results_output);

//    Access GetAccessIndex();

private:
//    mutex index_mutex;
    InvertedIndex index;
    vector<future<void>> futures;
    bool first = false;
};
