#include "search_server_test.h"

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
            const auto it_word = words_set.insert(word);
            ++words_map[*it_word.first][current_id];
        }
        ++current_id;
    }
}

map<size_t, size_t> DocsContainer::GetStats(const string_view word) const {
    if (words_map.count(word) == 0) {
        return {};
    }
    return words_map.at(word);
}

SearchServerTest::SearchServerTest(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServerTest::UpdateDocumentBase(istream &document_input) {
//    lock_guard<mutex> g(base_update_mutex);
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
//    vector<future<DocsContainer>> futures;
    vector<DocsContainer> futures_sync;
    for (const auto &page: pages) {
//        futures.push_back(async([=] { return DocsContainer(page, current_page * page_size); }));
        futures_sync.push_back(DocsContainer(page, current_page * page_size));
        ++current_page;
    }

    base.clear();
//    for (auto &f: futures) {
//        base.push_back(f.get());
//    }
    for (auto &f: futures_sync) {
        base.push_back(f);
    }
//    current_base ^= 1;
}

void SearchServerTest::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    while (query_input) {
        string line;
        getline(query_input, line);
        if (!line.empty()) {
            search_results_output << '{' << SearchRequest(line) << '}' << ' ';
        }
    }
}

string SearchServerTest::SearchRequest(const string &line) {
    string result = line + ':';
    set<string> request_words = ParseWordsSetFromLine(line);

    const auto &base = current_base ? base1 : base0;

    map<size_t, size_t> result_map;
//    vector<future<map<size_t, size_t>>> futures;
    vector<map<size_t, size_t>> futures_sync;
    for (const auto &word: request_words) {
        for (const auto &page: base) {
//            futures.push_back(async([=] { return page.GetStats(word); }));
            futures_sync.push_back(page.GetStats(word));
        }
    }
//    for (auto &f: futures) {
//        result_map.merge(f.get());
//    }
    for (auto &f: futures_sync) {
        result_map.merge(f);
    }

    for (auto it = result_map.rbegin(); it != result_map.rend(); ++it) {
        if (it->second == 0) {
            break;
        }
        result += " {docid: " + to_string(it->first) + ", hitcount: " + to_string(it->second) + "}";
    }

    return result;
}
