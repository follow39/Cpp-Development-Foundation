#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year

    const auto it_firstname = first_names.find(year);
    const auto it_lastname = last_names.find(year);

    // если и имя, и фамилия неизвестны
    if (it_firstname == first_names.end() && it_lastname == last_names.end()) {
      return "Incognito";
    } else if (it_firstname == first_names.end()) {
      return it_lastname->second + " with unknown first name";
    } else if (it_lastname == last_names.end()) {
      return it_firstname->second + " with unknown last name";
    } else {
      return it_firstname->second + " " + it_lastname->second;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};




int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  return 0;
}
