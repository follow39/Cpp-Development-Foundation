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


struct Access {
    lock_guard<mutex> guard;
    InvertedIndex &ref_to_value;
};

class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void UpdateDocumentBaseThread(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

    void AddQueriesThread(istream &query_input, ostream &search_results_output);

    Access GetAccessIndex();

private:
    mutex search_mutex;
    mutex index_mutex;
    InvertedIndex index;
    vector<future<void>> futures_update_vector;
    vector<future<void>> futures_queries_vector;
    bool first = false;
};
