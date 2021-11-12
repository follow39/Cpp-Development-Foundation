#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <future>

using namespace std;

using Domain = vector<string>;

vector<Domain> ReadDomains(istream &is) {
    size_t count;
    is >> count;
    is.ignore(1);

    vector<Domain> domains(count);
    for (size_t i = 0; i < count; ++i) {
        string domain;
        getline(is, domain);
        domain.push_back('.');
        string temp;
        for (char c: domain) {
            if (c == '.') {
                domains[i].push_back(temp);
                temp.clear();
            } else {
                temp.push_back(c);
            }
        }
    }
    return move(domains);
}

bool EqualDomains(const Domain &domain_to_check, const Domain &banned_domain) {
    if (domain_to_check.size() < banned_domain.size()) {
        return false;
    }
    for (long i = 0; i <= (domain_to_check.size() - banned_domain.size()); ++i) {
        bool result = true;
        for (long j = 0; j < banned_domain.size(); ++j) {
            result &= (domain_to_check[i + j] == banned_domain[j]);
        }
        if (result) {
            return true;
        }
    }
    return false;
}

bool SearchThread(const Domain &domain_to_check, const vector<Domain> &banned_domains) {
    for (const Domain &banned_domain: banned_domains) {
        if (EqualDomains(domain_to_check, banned_domain)) {
            return true;
        }
    }
    return false;
}

void func(istream &is, ostream &os) {
    const vector<Domain> banned_domains = ReadDomains(is);
    const vector<Domain> domains_to_check = ReadDomains(is);
//    vector<bool> results;

//    for (const Domain &domain_to_check: domains_to_check) {
//        for (const string &item: domain_to_check) {
//            cout << item << ' ';
//        }
//        cout << endl;
//    }
    for (const Domain &domain_to_check: domains_to_check) {
//        results.push_back(SearchThread(domain_to_check, banned_domains));
//        results.push_back(SearchThread(domain_to_check, banned_domains));
        os << (SearchThread(domain_to_check, banned_domains) ? "Bad" : "Good") << endl;
    }

//    for (const bool result: results) {
//        os << (result ? "Bad" : "Good") << '\n';
//    }
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