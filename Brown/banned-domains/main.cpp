#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <iterator>
#include <future>
#include <functional>
#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using namespace std;

template<typename Iterator>
class PaginatorPage {
public:
    PaginatorPage(Iterator begin, Iterator end, size_t size)
            : page_size(min(static_cast<size_t>(end - begin), size)),
              first(begin),
              last(begin + page_size) {}

    Iterator begin() {
        return first;
    }

    const Iterator begin() const {
        return first;
    }

    Iterator end() {
        return last;
    }

    const Iterator end() const {
        return last;
    }

    size_t size() const {
        return page_size;
    }

private:
    size_t page_size;
    Iterator first;
    Iterator last;
};

template<typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t size) {
        for (auto it = begin; it != end; it += size) {
            pages.push_back({it, end, size});
            if (pages.back().size() < size) {
                break;
            }
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }

private:
    vector<PaginatorPage<Iterator>> pages;
    size_t page_size;
};

template<typename C>
auto Paginate(C &c, size_t page_size) {
    return Paginator{c.begin(), c.end(), page_size};
}


bool IsSubdomain(string_view domain, string_view sub_domain) {
    domain.remove_prefix(domain.find_last_of('.', domain.size() - sub_domain.size()) + 1);
    return domain == sub_domain;
}

vector<string> ReadDomains(istream &is) {
    size_t count;
    is >> count;
    is.ignore(1);

    vector<string> domains;
    for (size_t i = 0; i < count; ++i) {
        string domain;
        getline(is, domain);
        domains.push_back(domain);
    }
    return move(domains);
}

vector<string> ReadBannedDomains(istream &is) {
    vector<string> domains = ReadDomains(is);

    for (string &domain: domains) {
        reverse(begin(domain), end(domain));
    }
    sort(begin(domains), end(domains));

    size_t insert_pos = 0;
    for (string &domain: domains) {
        if (insert_pos == 0 || !IsSubdomain(domain, domains[insert_pos - 1])) {
            swap(domains[insert_pos++], domain);
        }
    }
    domains.resize(insert_pos);

    for (string &domain: domains) {
        reverse(begin(domain), end(domain));
    }

    return move(domains);
}

bool SearchThread(const string &domain_to_check, const vector<string> &banned_domains) {
    for (const string &banned_domain: banned_domains) {
        if (IsSubdomain(domain_to_check, banned_domain)) {
            return true;
        }
    }
    return false;
}

template<typename Page>
string SearchPage(Page &page, const vector<string> &banned_domains) {
    string result;
    for (const auto &domain_to_check: page) {
        result += (SearchThread(domain_to_check, banned_domains) ? "Bad" : "Good");
        result += '\n';
    }
    return move(result);
}

void func(istream &is, ostream &os) {
    const vector<string> banned_domains = ReadDomains(is);
    const vector<string> domains_to_check = ReadDomains(is);

//    for (const string &domain_to_check: domains_to_check) {
//        os << (SearchThread(domain_to_check, banned_domains) ? "Bad" : "Good") << '\n';
//    }

//    const auto pages = Paginate(domains_to_check, domains_to_check.size() / 8);
    const auto pages = Paginate(domains_to_check, max(static_cast<size_t>(32), domains_to_check.size() / 32));
    vector<future<string>> futures;
    futures.reserve(pages.size());
    for (const auto &page: pages) {
        futures.push_back(async([&] { return SearchPage(page, ref(banned_domains)); }));
    }

    for (auto &result: futures) {
        os << result.get();
    }
}

int main() {
    func(cin, cout);
    return 0;
}

/*
4
ya.ru
maps.me
m.ya.ru
com
7
ya.ru
ya.com
m.maps.me
moscow.m.ya.ru
maps.com
maps.ru
ya.ya
 */