#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix) {
    string temp{prefix};
    return equal_range(range_begin, range_end, temp, [](const string& s1, const string& s2) { return s1[0] < s2[0]; });
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& prefix) {
    const int prefixSize = prefix.size();
    auto t = equal_range(range_begin, range_end, prefix, [prefixSize](const string& s1, const string& s2) {
        return s1.substr(0, prefixSize) < s2.substr(0, prefixSize);
    });
    return t;
}

int main() {
    {
        const vector<string> sorted_strings = {"anna", "moscow", "murmansk", "vologda"};

        const auto m_result =
                FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
        for (auto it = m_result.first; it != m_result.second; ++it) {
            cout << *it << " ";
        }
        cout << endl;

        const auto p_result =
                FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
        cout << (p_result.first - begin(sorted_strings)) << " " <<
                (p_result.second - begin(sorted_strings)) << endl;

        const auto z_result =
                FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
        cout << (z_result.first - begin(sorted_strings)) << " " <<
                (z_result.second - begin(sorted_strings)) << endl;
    }
    {
        const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

        const auto mo_result =
                FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
        for (auto it = mo_result.first; it != mo_result.second; ++it) {
            cout << *it << " ";
        }
        cout << endl;

        const auto mt_result =
                FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
        cout << (mt_result.first - begin(sorted_strings)) << " " <<
                (mt_result.second - begin(sorted_strings)) << endl;

        const auto na_result =
                FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
        cout << (na_result.first - begin(sorted_strings)) << " " <<
                (na_result.second - begin(sorted_strings)) << endl;
    }

    return 0;
}
