#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;


string prevChanges(const map<int, string>& input, int year)
{
    string result;
    vector<string> vec;

    for(auto& [key, value] : input)
    {
        if(key <= year)
        {
            if(value.empty())
                continue;

            if(vec.empty())
            {
                vec.push_back(value);
                continue;
            }

            if(value != vec.back())
            {
                vec.push_back(value);
            }
        }
        else
        {
            break;
        }
    }

    vec.pop_back();
    if(!vec.empty())
    {
        result = " (";
        while(!vec.empty())
        {
            result += vec.back();
            result += ", ";
            vec.pop_back();
        }
        result.pop_back();
        result.pop_back();
        result += ")";
    }

    return result;
}

string findByYear(const map<int, string>& input, int year)
{
    string result;
    for(auto& [key, value] : input)
    {
        if(key < year)
        {
            if(!value.empty())
            {
                result = value;
            }
        }
        else
        {
            break;
        }
    }

    return result;
}

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
            fname = findByYear(firstname, year);
        }
        if(lname == "")
        {
            lname = findByYear(lastname, year);
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
    string GetFullNameWithHistory(int year) {
        // получить имя и фамилию по состоянию на конец года year
        string fname = firstname[year];
        string lname = lastname[year];
        string result;

        if(fname.empty())
        {
            fname = findByYear(firstname, year);
        }
        if(!fname.empty())
        {
            fname += prevChanges(firstname, year);
        }

        if(lname.empty())
        {
            lname = findByYear(lastname, year);
        }
        if(!lname.empty())
        {
            lname += prevChanges(lastname, year);
        }

        if(fname.empty() && lname.empty())
        {
            result = "Incognito";
        }
        else if(!fname.empty() && lname.empty())
        {
            result = fname;
            result += " with unknown last name";
        }
        else if(fname.empty() && !lname.empty())
        {
            result = lname;
            result += " with unknown first name";
        }
        else if(!fname.empty() && !lname.empty())
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
    person.ChangeFirstName(1965, "Appolinaria");

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeLastName(1965, "Volkova");
    person.ChangeLastName(1965, "Volkova-Sergeeva");

    for (int year : {1964, 1965, 1966}) {
      cout << person.GetFullNameWithHistory(year) << endl;
    }


    return 0;
}


