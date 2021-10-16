#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "sys.h"

using namespace std;

void PrintStats(vector<Person> persons) {
    auto it = persons.begin();
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    sort(persons.begin(), persons.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.gender < rhs.gender;
    });
    it = find_if(persons.begin(), persons.end(), [](const Person& p) { return p.gender == Gender::MALE; });
    cout << "Median age for females = " <<
            ComputeMedianAge(persons.begin(), it) << endl;
    cout << "Median age for females = " <<
            ComputeMedianAge(it, persons.end()) << endl;
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
