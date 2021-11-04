#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

class InvertedIndex {
public:
    void Add(const string &document);

    const vector<pair<int, int>>& Lookup(const string &word) const;

    const string &GetDocument(int id) const {
        return docs[id];
    }

private:
    map<string, vector<pair<int, int>>> index;
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
    int docs_count = 0;
};
