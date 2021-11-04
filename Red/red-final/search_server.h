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
    void Add(const string &document);

    const vector<pair<int, int>> &Lookup(const string &word) const;

    const string &GetDocument(int id) const {
        return docs[id];
    }

private:
    map<string, vector<pair<int, int>>> index;
    vector<string> docs;
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

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

    string AddQueriesThread(string query_input);

    Access GetAccessIndex();

private:
    mutex index_mutex;
    InvertedIndex index;
    int docs_count = 0;
//    vector<future<void>> futures_queries;
};
