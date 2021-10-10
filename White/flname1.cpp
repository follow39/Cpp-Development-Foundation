#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
      firstname[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
      lastname[year] = last_name;
  }
  string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
      string fname = firstname[year];
      string lname = lastname[year];
      string result;

      if(fname == "")
      {
          for(auto& [key, value] : firstname)
          {
              if(key < year && value != "")
                  fname = value;
          }
      }
      if(lname == "")
      {
          for(auto& [key, value] : lastname)
          {
              if(key < year && value != "")
                  lname = value;
          }
      }

      if(fname == "" && lname == "")
      {
          result = "Incognito";
      }
      else if(fname != "" && lname == "")
      {
          result = fname;
          result += " with unknown last name";
      }
      else if(fname == "" && lname != "")
      {
          result = lname;
          result += " with unknown first name";
      }
      else if(fname != "" && lname != "")
      {
          result = fname;
          result += " ";
          result += lname;
      }

      return result;
  }
private:
  // приватные поля
  map<int, string> firstname;
  map<int, string> lastname;

};

int main()
{
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


