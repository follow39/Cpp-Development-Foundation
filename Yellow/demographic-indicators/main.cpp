#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "sys.h"

using namespace std;

void PrintStats(vector<Person> persons) {
    auto it1 = persons.begin();
    auto it2 = persons.begin();
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    sort(persons.begin(), persons.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.gender < rhs.gender;
    });
    it1 = find_if(persons.begin(), persons.end(), [](const Person& p) { return p.gender == Gender::MALE; });
    cout << "Median age for females = " <<
            ComputeMedianAge(persons.begin(), it1) << endl;
    cout << "Median age for males = " <<
            ComputeMedianAge(it1, persons.end()) << endl;
    sort(persons.begin(), it1, [](const Person& lhs, const Person& rhs) {
        return lhs.is_employed < rhs.is_employed;
    });
    sort(it1, persons.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.is_employed < rhs.is_employed;
    });
    it2 = find_if(persons.begin(), it1, [](const Person& p) { return p.is_employed; });
    cout << "Median age for employed females = " <<
            ComputeMedianAge(it2, it1) << endl;
    cout << "Median age for unemployed females = " <<
            ComputeMedianAge(persons.begin(), it2) << endl;
    it2 = find_if(it1, persons.end(), [](const Person& p) { return p.is_employed; });
    cout << "Median age for employed males = " <<
            ComputeMedianAge(it2, persons.end()) << endl;
    cout << "Median age for unemployed males = " <<
            ComputeMedianAge(it1, it2) << endl;
}

int main() {
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
    PrintStats(persons);
    return 0;
}
