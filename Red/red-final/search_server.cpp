#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string &line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
        ++docs_count;
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
) {
    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWords(current_query);

        vector<int> docid_count = vector<int>(docs_count);
        for (const auto &word: words) {
            for (const auto& [docid, count]: index.Lookup(word)) {
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

void InvertedIndex::Add(const string &document) {
    docs.push_back(document);

    const int docid = docs.size() - 1;
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
        return {};
    }
}
