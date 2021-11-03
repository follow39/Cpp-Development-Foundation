#pragma once

#include "paginator.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <string_view>
#include <future>
#include <mutex>
#include <iterator>
#include <set>
#include <sstream>

class DocsContainer {
public:
    template<typename ContainerOfVectors>
    explicit DocsContainer(const ContainerOfVectors &page, const size_t new_doc_id_start);

    map<size_t, size_t> GetStats(const set<string> &request_words) const; // return map<doc_id, count>

private:
    size_t doc_id_start;
//    set<string> words_set; // all words in this page. it save words for string_view in map
    map<string, map<size_t, size_t>> words_map;  // map<word, vector[doc_id]<count>>
//    map<size_t, map<string, size_t>> docs_map; // map<doc_id, map<word, count>>
};


class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    string SearchRequest(const string &line);

    // size_t current_database {0 , 1}
    // vector<pages> = Paginator(docs, docs.size()/8)
    size_t current_base = 0;
    mutex base_update_mutex;
    vector<DocsContainer> base0;
//    vector<mutex> base0_mutex;
    vector<DocsContainer> base1;
//    vector<mutex> base1_mutex;
};

