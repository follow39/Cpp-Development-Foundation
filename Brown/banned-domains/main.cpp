#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;


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

bool EqualDomains(const string &domain_to_check, const string &banned_domain) {
    size_t j = 0;
    for (size_t i = 0; i < domain_to_check.size(); ++i) {
        if (j + 1 == banned_domain.size()) {
            return true;
        }
        if (domain_to_check[i] == banned_domain[j]) {
            ++j;
        } else {
            j = 0;
        }
    }
    return false;
}

bool SearchThread(const string &domain_to_check, const vector<string> &banned_domains) {
    for (const auto &banned_domain: banned_domains) {
        if (EqualDomains(domain_to_check, banned_domain)) {
            return true;
        }
    }
    return false;
}

void func(istream &is, ostream &os) {
    const vector<string> banned_domains = ReadDomains(is);
    const vector<string> domains_to_check = ReadDomains(is);
    vector<bool> results;

    for (const auto &domain_to_check: domains_to_check) {
        results.push_back(SearchThread(domain_to_check, banned_domains));
    }

    for (const bool result: results) {
        os << (result ? "Bad" : "Good") << '\n';
    }
}

int main() {
    func(cin, cout);
    return 0;
}