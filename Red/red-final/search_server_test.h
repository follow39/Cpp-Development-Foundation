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

class DocsContainer {
public:
    template <typename ContainerOfVectors>
     explicit DocsContainer(const ContainerOfVectors& page, const size_t doc_id_start);

    // const pair<doc_id_start, vector<count>> GetStats(const string_view word) const

private:
    // size_t doc_id_start
    // mutex container_mutex
    // vector<string> docs
    // map<string_view, vector<size_t>> - map<word, vector[doc_id]<count>>
};


class SearchServerTest {
public:
    SearchServerTest() = default;

    explicit SearchServerTest(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    // size_t current_database {0 , 1}
    // vector<pages> = Paginator(docs, docs.size()/8)
     vector<DocsContainer> base1;
     vector<mutex> base1_mutex;
    // vector<DocsContainer> base2
    // vector<mutex> base2_mutex
};

