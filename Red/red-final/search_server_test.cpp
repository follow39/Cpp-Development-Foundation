#include "search_server_test.h"

using namespace std;

vector<string> ParseWordsFromDoc(const string& doc) {
    stringstream ss(doc);
    vector<string> result;
    while(ss) {
        ss >> ws;
        string temp;
        ss >> temp;
        if(!temp.empty()) {
            result.push_back(temp);
        }
    }
    return result;
}

template<typename ContainerOfVectors>
DocsContainer::DocsContainer(const ContainerOfVectors &page, const size_t new_doc_id_start)
        : doc_id_start(new_doc_id_start) {
    size_t current_id = 0;
    for (const auto &doc: page) {
        auto temp_vector = ParseWordsFromDoc(doc);
        for(auto& word : temp_vector) {
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
    map<size_t, size_t> result;
    const auto &docs_count_vector = words_map.at(word);

    for (size_t i = 0; i < docs_count_vector.size(); ++i) {
        if (docs_count_vector[i] != 0) {
            result[doc_id_start + i] = docs_count_vector[i];
        }
    }

    return result;
}

SearchServerTest::SearchServerTest(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServerTest::UpdateDocumentBase(istream &document_input) {
    lock_guard<mutex> g(base_update_mutex);
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
    for (const auto &page: pages) {
        futures.push_back(async([=] { return DocsContainer(page, current_page * page_size); }));
        ++current_page;
    }

    base.clear();
    for (auto &f: futures) {
        base.push_back(f.get());
    }
    current_base ^= 1;
}

void SearchServerTest::AddQueriesStream(istream &query_input, ostream &search_results_output) {

}
