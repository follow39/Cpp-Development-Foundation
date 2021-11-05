#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

auto Lock(mutex &m) {
    return lock_guard<mutex>{m};
}

//vector<string> SplitIntoWords(const string &line) {
//    istringstream words_input(line);
//    return {istream_iterator<string>(words_input), istream_iterator<string>()};
//}
vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> result;
    size_t space = line.find_first_not_of(' ');
    line.remove_prefix(space);
    while (true) {
        space = line.find(' ');
        result.push_back(line.substr(0, space));
        space = line.find_first_not_of(' ', space);
        if (space == std::string_view::npos) {
            break;
        } else {
            line.remove_prefix(space);
        }
    }
    return move(result);
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    if (!first) {
        first = true;
        UpdateDocumentBaseThread(document_input);
    } else {
        futures_update_vector.push_back(async([&] { return UpdateDocumentBaseThread(document_input); }));
    }
}

void SearchServer::UpdateDocumentBaseThread(istream &document_input) {
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document);) {
        if (!current_document.empty()) {
            new_index.Add(move(current_document));
        }
    }
    auto access = GetAccessIndex();
    swap(access.ref_to_value, new_index);
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    if (futures_queries_vector.size() > 8) {
        futures_queries_vector.clear();
    }
    futures_queries_vector.push_back(async([&] { return AddQueriesThread(query_input, search_results_output); }));
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

        int max_docid = 0;
        vector<int> docid_count = vector<int>(50000);
        for (const auto &word: words) {
            for (const auto&[docid, count]: GetAccessIndex().ref_to_value.Lookup(word)) {
                max_docid = max(docid, max_docid);
                docid_count[docid] += count;
            }
        }

        vector<pair<int, int>> search_results;
        search_results.reserve(max_docid);
        for (int i = 0; i <= max_docid; ++i) {
            if (docid_count[i] != 0) {
                search_results.emplace_back(i, docid_count[i]);
            }
        }

        auto it_mid = Head(search_results, 5ul).end();
        partial_sort(search_results.begin(), it_mid, search_results.end(),
                     [](pair<int, int> lhs, pair<int, int> rhs) {
                         return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second > rhs.second;
                     });

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

void InvertedIndex::Add(string document) {
    const int docid = current_docid++;
    auto it_doc = documents.insert(documents.end(), move(document));
    for (const auto &word: SplitIntoWords(*it_doc)) {
        if (index[word].empty() || index[word].back().first != docid) {
            index[word].push_back({docid, 1});
        } else {
            ++index[word].back().second;
        }
    }
}

//const vector<pair<int, int>> &InvertedIndex::Lookup(const string &word) const {
const vector<pair<int, int>> &InvertedIndex::Lookup(const string_view word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty_vector;
    }
}
