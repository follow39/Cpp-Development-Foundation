#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

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
    InvertedIndex new_index;

    vector<string> docs_vector;
    while (document_input) {
        string temp;
        getline(document_input, temp);
        if (!temp.empty()) {
            docs_vector.push_back(temp);
        }
    }

    vector<future<void>> futures;
    for (auto &doc: docs_vector) {
//        futures.push_back(async([&new_index, &doc] { new_index.Add(doc); }));
        new_index.Add(move(doc));
    }

    for (auto &f: futures) {
        f.get();
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
) {
    for (string current_query; getline(query_input, current_query);) {
        if(current_query.empty()) {
            continue;
        }
        const auto words = SplitIntoWords(current_query);

        map<size_t, size_t> docid_count;

        vector<future<map<size_t, size_t>>> futures;
        futures.reserve(words.size());
        for (const auto &word: words) {
            futures.push_back(async([=] { return index.Lookup(word); }));
        }
        for (auto &f: futures) {
            auto temp = f.get();
            for(auto& [docid, count] : temp) {
                docid_count[docid] += count;
            }
        }

        vector<pair<size_t, size_t>> search_results(docid_count.begin(), docid_count.end());
        auto it_mid = Head(search_results, 5).end();
        partial_sort(search_results.begin(), it_mid, search_results.end(),
                     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
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
        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string &document) {
    docs.push_back(document);
    const size_t docid = docs.size() - 1;

    for (const auto &word: SplitIntoWords(document)) {
        ++index[word].second[docid];
    }
}

map<size_t, size_t> InvertedIndex::Lookup(const string &word) {
    auto it = index.find(word);
    if (it == index.end()) {
        return {};
    }
    auto g = Lock(it->second.first);
    return it->second.second;
}

InvertedIndex &InvertedIndex::operator=(InvertedIndex &&other) noexcept {
    index = move(other.index);
    docs = move(other.docs);
    return *this;
}
