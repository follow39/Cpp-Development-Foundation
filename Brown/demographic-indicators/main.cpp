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

string GetMostPopularName(const vector<Person> &people, char gender) {
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
    return most_popular_name;
}

int main() {
    const vector<Person> people = [] {
        vector<Person> people = ReadPeople(cin);
        sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {
            return lhs.age < rhs.age;
        });
        return move(people);
    }();

    const vector<int> age_vector = [people] {
        vector<int> age_vector(150);
        vector<int> result;
        for (const auto &person: people) {
            ++age_vector[person.age];
        }
        partial_sum(age_vector.rbegin(), age_vector.rend(), back_inserter(result));
        reverse(result.begin(), result.end());
        return move(result);
    }();
    const vector<int> wealthy_vector = [people] {
        vector<int> wealthy_vector;
        vector<int> result;
        wealthy_vector.reserve(people.size());
        for (const auto &person: people) {
            wealthy_vector.push_back(person.income);
        }
        sort(wealthy_vector.begin(), wealthy_vector.end());
        partial_sum(wealthy_vector.rbegin(), wealthy_vector.rend(), back_inserter(result));
        return move(result);
    }();

    const string most_popular_name_m = GetMostPopularName(people, 'M');
    const string most_popular_name_w = GetMostPopularName(people, 'W');

    for (string command; cin >> command;) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;
            cout << "There are " << age_vector[adult_age]
                 << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;
            cout << "Top-" << count << " people have total income " << wealthy_vector[count - 1] << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;
            cout << "Most popular name among people of gender " << gender << " is "
                 << ((gender == 'M') ? most_popular_name_m : most_popular_name_w) << '\n';
        }
    }
}

