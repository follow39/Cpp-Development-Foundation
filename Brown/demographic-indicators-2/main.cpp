#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

//enum class Gender {
//    FEMALE,
//    MALE
//};
//
//struct Person {
//    int age;  // возраст
//    Gender gender;  // пол
//    bool is_employed;  // имеет ли работу
//};
//
//template<typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end);

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
//template<typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
//    if (range_begin == range_end) {
//        return 0;
//    }
//    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
//    auto middle = begin(range_copy) + range_copy.size() / 2;
//    nth_element(
//            begin(range_copy), middle, end(range_copy),
//            [](const Person &lhs, const Person &rhs) {
//                return lhs.age < rhs.age;
//            }
//    );
//    return middle->age;
//}

void PrintStats(vector<Person> persons) {
    auto it_gender = partition(persons.begin(), persons.end(),
                               [](const Person &person) { return person.gender == Gender::FEMALE; });
    auto it_w_e = partition(persons.begin(), it_gender,
                            [](const Person &person) { return person.is_employed; });
    auto it_m_e = partition(it_gender, persons.end(),
                            [](const Person &person) { return person.is_employed; });

    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << '\n';
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it_gender) << '\n';
    cout << "Median age for males = " << ComputeMedianAge(it_gender, persons.end()) << '\n';
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it_w_e) << '\n';
    cout << "Median age for unemployed females = " << ComputeMedianAge(it_w_e, it_gender) << '\n';
    cout << "Median age for employed males = " << ComputeMedianAge(it_gender, it_m_e) << '\n';
    cout << "Median age for unemployed males = " << ComputeMedianAge(it_m_e, persons.end()) << '\n';
}

int main() {
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
    PrintStats(persons);
    return 0;
}
