#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <iterator>

using namespace std;

bool IsSubdomain(string_view domain, string_view sub_domain) {
    if (domain.size() < sub_domain.size()) {
        return false;
    }
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
    const vector<string> domains = ReadDomains(is);
    vector<string> result;

    for (size_t i = 0; i < domains.size(); ++i) {
        bool hasSubdomain = false;
        for (size_t j = 0; j < domains.size(); ++j) {
            if (i == j) {
                continue;
            }
            hasSubdomain |= IsSubdomain(domains[i], domains[j]);
            if (hasSubdomain) {
                if (domains[i] == domains[j] &&
                    std::find(result.begin(), result.end(), domains[i]) == result.end()) {
                    hasSubdomain = false;
                }
                break;
            }
        }
        if (!hasSubdomain) {
            result.push_back(domains[i]);
        }
    }

    return move(result);
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
    const vector<string> banned_domains = ReadBannedDomains(is);
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