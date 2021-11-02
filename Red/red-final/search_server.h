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

    list<size_t> Lookup(const string &word) const;

    const string &GetDocument(size_t id) const {
        return docs[id];
    }

private:
    map<string, list<size_t>> index;
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
    map<size_t, map<string_view, size_t>> m; // map<doc_id, map<word, count>>
    // map<word, map<doc_id, count>>
    // 2 maps with swap
    // size_t current_database {0 , 1}
    // vector<pages> = Paginator(docs, docs.size()/8)
    // vector<DocsContainer> base1
    // vector<mutex> base1_mutex
    // vector<DocsContainer> base2
    // vector<mutex> base2_mutex
};

class DocsContainer {
public:
    // DocsContainer(PaginatorPage, size_t doc_id_start)

    // const pair<doc_id_start, vector<count>> GetStats(const string_view word) const

private:
    // size_t doc_id_start
    // mutex container_mutex
    // vector<string> docs
    // map<string_view, vector<size_t>> - map<word, vector[doc_id]<count>>
};