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
        if(key <= year)
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
    Person(const string& fname, const string& lname, int age)
    {
        firstname[age] = fname;
        lastname[age] = lname;
        born = age;
    }
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        if(year >= born)
        {
            firstname[year] = first_name;
        }
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        if(year >= born)
        {
            lastname[year] = last_name;
        }
    }
    string GetFullName(int year) const {
        // получить имя и фамилию по состоянию на конец года year
        if(year < born)
        {
            return "No person";
        }

        string fname;
        string lname;
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
    string GetFullNameWithHistory(int year) const {
        // получить имя и фамилию по состоянию на конец года year
        if(year < born)
        {
            return "No person";
        }

        string fname;
        string lname;
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
    int born;
};

int main()
{
    Person person("-1_first", "-1_last", -1);

    int year = -1;
    person.ChangeFirstName(year, std::to_string(2) + "_first");
    person.ChangeLastName(year, std::to_string(2) + "_last");

    year = 5;
    person.ChangeFirstName(year, std::to_string(year) + "_first");
    person.ChangeLastName(year, std::to_string(year) + "_last");

    year = 7;
    std::cout << "year: " << year << '\n';
    std::cout << person.GetFullName(year) << '\n';
    std::cout << person.GetFullNameWithHistory(year) << '\n';


    return 0;
}


