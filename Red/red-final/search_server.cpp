#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

auto Lock(mutex &m) {
    return lock_guard<mutex>{m};
}

vector<string> SplitIntoWords(const string &line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
//    vector<future<void>> futures;
    if (!first) {
        first = true;
        UpdateDocumentBaseThread(document_input);
//        this_thread::sleep_for(static_cast<chrono::nanoseconds>(1000));
    } else {
        futures.clear();
        futures.push_back(async([&] { return UpdateDocumentBaseThread(document_input); }));
    }
}

void SearchServer::UpdateDocumentBaseThread(istream &document_input) {
    InvertedIndex new_index;
    int new_docs_count = 0;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(current_document);
        ++new_docs_count;
    }

    auto access = GetAccessIndex();
    access.ref_to_value = move(new_index);
    docs_count = new_docs_count;
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    vector<future<void>> futures_local;
    futures_local.push_back(async([&] { return AddQueriesThread(query_input, search_results_output); }));
//    futures.push_back(async([&] { return AddQueriesThread(query_input, search_results_output); }));
}

void SearchServer::AddQueriesThread(istream &query_input, ostream &search_results_output) {
    vector<string> query_vector;

    while (query_input) {
        string temp;
        getline(query_input, temp);
        if (!temp.empty()) {
            query_vector.push_back(move(temp));
        }
    }
    for (string &current_query: query_vector) {
        const auto words = SplitIntoWords(current_query);

        vector<int> docid_count = vector<int>(docs_count);
        for (const auto &word: words) {
            auto temp = GetAccessIndex().ref_to_value.Lookup(word);
            for (const auto&[docid, count]: temp) {
                docid_count[docid] += count;
            }
        }

        vector<pair<int, int>> search_results;
        search_results.reserve(docs_count);
        for (int i = 0; i < docs_count; ++i) {
            if (docid_count[i] != 0) {
                search_results.emplace_back(i, docid_count[i]);
            }
        }

        auto it_mid = Head(search_results, 5ul).end();
        partial_sort(search_results.begin(), it_mid, search_results.end(),
                     [](pair<int, int> lhs, pair<int, int> rhs) {
                         if (lhs.second != rhs.second) {
                             return lhs.second > rhs.second;
                         }
                         return lhs.first < rhs.first;
                     }
        );

        search_results_output << current_query << ':';
        for (auto[docid, hitcount]: Head(search_results, 5)) {
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';
    }
}

Access SearchServer::GetAccessIndex() {
    return Access{Lock(index_mutex), index};
}

void InvertedIndex::Add(string &document) {
    const int docid = current_docid++;
    for (const auto &word: SplitIntoWords(document)) {
        if (index[word].empty() || index[word].back().first != docid) {
            index[word].push_back({docid, 1});
        } else {
            ++index[word].back().second;
        }
    }
}

const vector<pair<int, int>> &InvertedIndex::Lookup(const string &word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty_vector;
    }
}
