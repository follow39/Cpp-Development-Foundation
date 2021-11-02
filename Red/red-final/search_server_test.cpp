#include "search_server_test.h"

using namespace std;

template<typename ContainerOfVectors>
DocsContainer::DocsContainer(const ContainerOfVectors &page, const size_t doc_id_start) {

}

SearchServerTest::SearchServerTest(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServerTest::UpdateDocumentBase(istream &document_input) {
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
}

void SearchServerTest::AddQueriesStream(istream &query_input, ostream &search_results_output) {

}
