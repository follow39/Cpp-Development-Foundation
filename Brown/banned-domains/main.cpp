#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <iterator>
#include <future>
#include <functional>

using namespace std;


bool IsSubdomain(string_view domain, string_view sub_domain) {
    if (domain.size() < sub_domain.size()) {
        return false;
    }
    domain.remove_prefix(domain.size() - sub_domain.size());
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

void func(istream &is, ostream &os) {
    const vector<string> banned_domains = ReadDomains(is);
    const vector<string> domains_to_check = ReadDomains(is);

    for (const string &domain_to_check: domains_to_check) {
        os << (SearchThread(domain_to_check, banned_domains) ? "Bad" : "Good") << '\n';
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