#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

bool operator==(const Person &lhs, const Person &rhs) {
    return lhs.age == rhs.age
           && lhs.gender == rhs.gender
           && lhs.is_employed == rhs.is_employed;
}

ostream &operator<<(ostream &stream, const Person &person) {
    return stream << "Person(age=" << person.age
                  << ", gender=" << static_cast<int>(person.gender)
                  << ", is_employed=" << boolalpha << person.is_employed << ")";
}

struct AgeStats {
    int total;
    int females;
    int males;
    int employed_females;
    int unemployed_females;
    int employed_males;
    int unemployed_males;
};

template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename iterator_traits<InputIt>::value_type> range_copy(
            range_begin,
            range_end
    );
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person &lhs, const Person &rhs) {
                return lhs.age < rhs.age;
            }
    );
    return middle->age;
}

vector<Person> ReadPersons(istream &in_stream = cin) {
    int person_count;
    in_stream >> person_count;
    vector<Person> persons;
    persons.reserve(person_count);
    for (int i = 0; i < person_count; ++i) {
        int age, gender, is_employed;
        in_stream >> age >> gender >> is_employed;
        Person person{
                age,
                static_cast<Gender>(gender),
                is_employed == 1
        };
        persons.push_back(person);
    }
    return persons;
}

AgeStats ComputeStats(vector<Person> persons) {
    //                 persons
    //                |       |
    //          females        males
    //         |       |      |     |
    //      empl.  unempl. empl.   unempl.

    auto females_end = partition(
            begin(persons), end(persons),
            [](const Person &p) {
                return p.gender == Gender::FEMALE;
            }
    );
    auto employed_females_end = partition(
            begin(persons), females_end,
            [](const Person &p) {
                return p.is_employed;
            }
    );
    auto employed_males_end = partition(
            females_end, end(persons),
            [](const Person &p) {
                return p.is_employed;
            }
    );

    return {
            ComputeMedianAge(begin(persons), end(persons)),
            ComputeMedianAge(begin(persons), females_end),
            ComputeMedianAge(females_end, end(persons)),
            ComputeMedianAge(begin(persons), employed_females_end),
            ComputeMedianAge(employed_females_end, females_end),
            ComputeMedianAge(females_end, employed_males_end),
            ComputeMedianAge(employed_males_end, end(persons))
    };
}

void PrintStats(const AgeStats &stats,
                ostream &out_stream = cout) {
    out_stream << "Median age = "
               << stats.total << endl
               << "Median age for females = "
               << stats.females << endl
               << "Median age for males = "
               << stats.males << endl
               << "Median age for employed females = "
               << stats.employed_females << endl
               << "Median age for unemployed females = "
               << stats.unemployed_females << endl
               << "Median age for employed males = "
               << stats.employed_males << endl
               << "Median age for unemployed males = "
               << stats.unemployed_males << endl;
}

void TestComputeMedianAge() {
    {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> random_0_1(0, 1);
        std::uniform_int_distribution<int> random_0_74(0, 74);
        std::uniform_int_distribution<int> random_76_150(76, 150);
        int persons_count = 100'001;
        vector<Person> persons;
        persons.reserve(persons_count);
        persons.push_back({75, Gender::FEMALE, true});
        for (int i = 0; i < (persons_count - 1) / 2; ++i) {
            persons.emplace_back(Person{random_0_74(e1), static_cast<Gender>(random_0_1(e1)),
                                        static_cast<bool>(random_0_1(e1))});
        }
        for (int i = 0; i < (persons_count - 1) / 2; ++i) {
            persons.emplace_back(Person{random_76_150(e1), static_cast<Gender>(random_0_1(e1)),
                                        static_cast<bool>(random_0_1(e1))});
        }

        int attempts = 100;
        for (int i = 0; i < attempts; ++i) {
            shuffle(persons.begin(), persons.end(), r);
            int result = ComputeMedianAge(persons.begin(), persons.end());
            ASSERT_EQUAL(result, 75);
        }
    }
}

void TestReadPersons() {
    {
        vector<Person> expected;
        stringstream ss("0");
        vector<Person> result = ReadPersons(ss);
        ASSERT_EQUAL(result, expected);
    }
    {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> random_0_1(0, 1);
        std::uniform_int_distribution<int> random_1_100(1, 100);
        int persons_count = 100'000;
        vector<Person> expected;
        expected.reserve(persons_count);
        for (int i = 0; i < persons_count; ++i) {
            expected.emplace_back(Person{random_1_100(e1), static_cast<Gender>(random_0_1(e1)),
                                         static_cast<bool>(random_0_1(e1))});
        }
        stringstream ss;
        ss << expected.size() << '\n';
        for (const auto &person: expected) {
            ss << person.age << ' ' << static_cast<int>(person.gender) << ' '
               << static_cast<int>(person.is_employed) << '\n';
        }
        vector<Person> result = ReadPersons(ss);
        ASSERT_EQUAL(result, expected);
    }
}

bool operator==(const AgeStats &lhs, const AgeStats &rhs) {
    return lhs.total == rhs.total &&
           lhs.females == rhs.females &&
           lhs.males == rhs.males &&
           lhs.employed_females == rhs.employed_females &&
           lhs.unemployed_females == rhs.unemployed_females &&
           lhs.employed_males == rhs.employed_males &&
           lhs.unemployed_males == rhs.unemployed_males;
}

ostream &operator<<(ostream &os, const AgeStats &stats) {
    os << '[' << stats.total << ", "
       << to_string(stats.females) << ", "
       << to_string(stats.males) << ", "
       << to_string(stats.employed_females) << ", "
       << to_string(stats.unemployed_females) << ", "
       << to_string(stats.employed_males) << ", "
       << to_string(stats.unemployed_males) << ']';
    return os;
}

void TestComputeStats() {
    {
        vector<Person> persons = {
                {31, Gender::MALE,   false},
                {40, Gender::FEMALE, true},
                {24, Gender::MALE,   true},
                {20, Gender::FEMALE, true},
                {80, Gender::FEMALE, false},
                {78, Gender::MALE,   false},
                {10, Gender::FEMALE, false},
                {55, Gender::MALE,   true},
        };

        AgeStats expected = {
                40,
                40,
                55,
                40,
                80,
                55,
                78
        };
        AgeStats result = ComputeStats(persons);
        ASSERT_EQUAL(result, expected);
    }
}

void TestPrintStats() {
    {
        AgeStats stats = {
                40,
                40,
                55,
                40,
                80,
                55,
                78
        };
        stringstream expected;
        expected << "Median age = " << stats.total << endl
                 << "Median age for females = " << stats.females << endl
                 << "Median age for males = " << stats.males << endl
                 << "Median age for employed females = " << stats.employed_females << endl
                 << "Median age for unemployed females = " << stats.unemployed_females << endl
                 << "Median age for employed males = " << stats.employed_males << endl
                 << "Median age for unemployed males = " << stats.unemployed_males << endl;
        stringstream result;
        PrintStats(stats, result);
        ASSERT_EQUAL(result.str(), expected.str());
    }
}

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestComputeMedianAge);
    RUN_TEST(tr, TestReadPersons);
    RUN_TEST(tr, TestComputeStats);
    RUN_TEST(tr, TestPrintStats);
}

int main() {
    TestAll();
    PrintStats(ComputeStats(ReadPersons()));
    return 0;
}

/*
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  */