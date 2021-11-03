#include "search_server.h"

using namespace std;

vector<string> ParseWordsVectorFromLine(const string &doc) {
    stringstream ss(doc);
    vector<string> result;
    while (ss) {
        ss >> ws;
        string temp;
        ss >> temp;
        if (!temp.empty()) {
            result.push_back(temp);
        }
    }
    return move(result);
}

set<string> ParseWordsSetFromLine(const string &doc) {
    stringstream ss(doc);
    set<string> result;
    while (ss) {
        ss >> ws;
        string temp;
        ss >> temp;
        if (!temp.empty()) {
            result.insert(temp);
        }
    }
    return move(result);
}

template<typename ContainerOfVectors>
DocsContainer::DocsContainer(const ContainerOfVectors &page, const size_t new_doc_id_start)
        : doc_id_start(new_doc_id_start) {
    size_t current_id = 0;
    for (const auto &doc: page) {
        auto temp_vector = ParseWordsVectorFromLine(doc);
        for (auto &word: temp_vector) {
            ++words_map[word][current_id];
        }
        ++current_id;
    }
}

map<size_t, size_t> DocsContainer::GetStats(const set<string> &request_words) const {
    map<size_t, size_t> result;

    for (const auto &word: request_words) {
        if (words_map.count(word) == 0) {
            continue;
        }
        for (const auto&[doc_id, count]: words_map.at(word)) {
            result[doc_id_start + doc_id] += count;
        }
    }

    return result;
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    lock_guard<mutex> g(base_update_mutex);
    current_base ^= 1;
    auto &base = current_base ? base1 : base0;

    vector<string> docs;
    while (document_input) {
        string temp;
        getline(document_input, temp);
        if (!temp.empty()) {
            docs.push_back(temp);
        }
    }

    const size_t page_size = max(docs.size() / 8, static_cast<size_t>(1));
    size_t current_page = 0;
    const auto pages = Paginate(docs, page_size);
    vector<future<DocsContainer>> futures;
//    vector<DocsContainer> futures_sync;
    for (const auto &page: pages) {
        futures.push_back(async([=] { return DocsContainer(page, current_page * page_size); }));
//        futures_sync.push_back(DocsContainer(page, current_page * page_size));
        ++current_page;
    }

    base.clear();
    for (auto &f: futures) {
        base.push_back(f.get());
    }
//    for (auto &f: futures_sync) {
//        base.push_back(f);
//    }
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    while (query_input) {
        string line;
        getline(query_input, line);
        if (!line.empty()) {
            search_results_output << SearchRequest(line) << endl;
        }
    }
}

string SearchServer::SearchRequest(const string &line) {
    const auto &base = current_base ? base1 : base0;
    string result = line + ':';
    set<string> request_words = ParseWordsSetFromLine(line);

    map<size_t, size_t> result_map;
    vector<future<map<size_t, size_t>>> futures;
//    vector<map<size_t, size_t>> futures_sync;
    for (const auto &page: base) {
        futures.push_back(async([=] { return page.GetStats(request_words); }));
//        futures_sync.push_back(page.GetStats(request_words));
    }
    for (auto &f: futures) {
        result_map.merge(f.get());
    }
//    for (auto &f: futures_sync) {
//        result_map.merge(f);
//    }

    vector<pair<size_t, size_t>> result_vector{result_map.begin(), result_map.end()};
    sort(result_vector.begin(), result_vector.end(), [](const auto &lhs, const auto &rhs) {
        if (lhs.second != rhs.second) {
            return lhs.second > rhs.second;
        }
        return lhs.first < rhs.first;
    });
    size_t cnt = 0;
    for (const auto &p: result_vector) {
        if (cnt++ >= 5) {
            break;
        }
        result += " {docid: " + to_string(p.first) + ", hitcount: " + to_string(p.second) + "}";
    }

    return result;
}
