#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <map>

using namespace std;

template<typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin), last(end) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template<typename Collection>
auto Head(Collection &v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream &input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person &p: result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }

    return result;
}

int main() {
    const vector<Person> people = [] {
        vector<Person> people = ReadPeople(cin);
        sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {
            return lhs.age < rhs.age;
        });
        return people;
    }();


    for (string command; cin >> command;) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;

            auto adult_begin = lower_bound(
                    begin(people), end(people), adult_age, [](const Person &lhs, int age) {
                        return lhs.age < age;
                    }
            );

            cout << "There are " << std::distance(adult_begin, end(people))
                 << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;

            vector<Person> temp(count);
            partial_sort_copy(
                    people.begin(), people.end(),
                    temp.begin(), temp.end(),
                    [](const Person &lhs, const Person &rhs) {
                        return lhs.income > rhs.income;
                    });

            int total_income = accumulate(
                    temp.begin(), temp.end(), 0, [](int cur, Person &p) {
                        return p.income += cur;
                    }
            );
            cout << "Top-" << count << " people have total income " << total_income << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;

            map<string, int> names;
            for (const auto &person: people) {
                if (person.is_male == (gender == 'M')) {
                    ++names[person.name];
                }
            }
            string most_popular_name;
            int most_popular_name_count = 0;
            for (const auto&[name, count]: names) {
                if ((count > most_popular_name_count) ||
                    (count == most_popular_name_count && name < most_popular_name)) {
                    most_popular_name = name;
                    most_popular_name_count = count;
                }
            }
            cout << "Most popular name among people of gender " << gender << " is "
                 << most_popular_name << '\n';
        }
    }
}

