#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
    }
    void ChangeLastName(int year, const string& last_name) {
    }
    string GetFullName(int year) {
        return "";
    }
};

//bool operator==(Person& lhs, Person& rhs) {
//    return lhs.GetFullName(numeric_limits<int>::max()) == rhs.GetFullName(numeric_limits<int>::max());
//}

bool TestPerson(Person& p, int year, const string& expected) {
    if(p.GetFullName(year) == expected)
        return true;
    return false;
}

const string wufn = " with unknown first name";
const string wuln = " with unknown last name";

void TestEmpty() {
    {
        Person person;
        string expected = "Incognito";
        Assert(TestPerson(person, numeric_limits<int>::min(), expected), "TestEmpty1");
    }
    {
        Person person;
        string expected = "Incognito";
        Assert(TestPerson(person, 0, expected), "TestEmpty2");
    }
    {
        Person person;
        string expected = "Incognito";
        Assert(TestPerson(person, numeric_limits<int>::max(), expected), "TestEmpty3");
    }
}

void TestChangesFirstName() {
    {
        Person person;
        string newNameF = "Ivan";
        string expected = newNameF + wufn;
        int year = 0;
        person.ChangeFirstName(year, newNameF);
        Assert(TestPerson(person, year, expected), "TestNegativeYear4");
        newNameF = "Igor";
        expected = newNameF + wufn;
        person.ChangeFirstName(year, newNameF);
    }
}

void TestChangesLastName() {
}

void TestChangesYear() {
    // zero
    {
        Person person;
        string expected = "Incognito";
        int year = 0;
        Assert(TestPerson(person, year, expected), "TestZeroYear1");
    }
    {
        Person person;
        string newNameF = "Ivan";
        string expected = newNameF + wufn;
        int year = 0;
        person.ChangeFirstName(year, newNameF);
        Assert(TestPerson(person, year, expected), "TestZeroYear2");
    }
    {
        Person person;
        string newNameL = "Ivanov";
        string expected = newNameL + wuln;
        int year = 0;
        person.ChangeLastName(year, newNameL);
        Assert(TestPerson(person, year, expected), "TestZeroYear3");
    }
    {
        Person person;
        string newNameF = "Ivan";
        string newNameL = "Ivanov";
        string expected = "Ivan Ivanov";
        int year = 0;
        person.ChangeFirstName(year, newNameF);
        person.ChangeLastName(year, newNameL);
        Assert(TestPerson(person, year, expected), "TestZeroYear4");
    }
    // negative
    {
        Person person;
        string expected = "Incognito";
        int year = -999;
        Assert(TestPerson(person, year, expected), "TestNegativeYear1");
    }
    {
        Person person;
        string newNameF = "Ivan";
        string expected = newNameF + wufn;
        int year = -999;
        person.ChangeFirstName(year, newNameF);
        Assert(TestPerson(person, year, expected), "TestNegativeYear2");
    }
    {
        Person person;
        string newNameL = "Ivanov";
        string expected = newNameL + wuln;
        int year = -999;
        person.ChangeLastName(year, newNameL);
        Assert(TestPerson(person, year, expected), "TestNegativeYear3");
    }
    {
        Person person;
        string newNameF = "Ivan";
        string newNameL = "Ivanov";
        string expected = "Ivan Ivanov";
        int year = -999;
        person.ChangeFirstName(year, newNameF);
        person.ChangeLastName(year, newNameL);
        Assert(TestPerson(person, year, expected), "TestNegativeYear4");
    }
    // positive
    {
        Person person;
        string expected = "Incognito";
        int year = -999;
        Assert(TestPerson(person, year, expected), "TestPositiveYear1");
    }
    {
        Person person;
        string newNameF = "Ivan";
        string expected = newNameF + wufn;
        int year = -999;
        person.ChangeFirstName(year, newNameF);
        Assert(TestPerson(person, year, expected), "TestPositiveYear2");
    }
    {
        Person person;
        string newNameL = "Ivanov";
        string expected = newNameL + wuln;
        int year = -999;
        person.ChangeLastName(year, newNameL);
        Assert(TestPerson(person, year, expected), "TestPositiveYear3");
    }
    {
        Person person;
        string newNameF = "Ivan";
        string newNameL = "Ivanov";
        string expected = "Ivan Ivanov";
        int year = -999;
        person.ChangeFirstName(year, newNameF);
        person.ChangeLastName(year, newNameL);
        Assert(TestPerson(person, year, expected), "TestPositiveYear4");
    }
}

void TestAll() {
    TestRunner runner;

}

int main() {
    TestAll();

    return 0;
}
