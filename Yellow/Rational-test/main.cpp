#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

//class Rational {
//public:

//    Rational();
//    Rational(int numerator, int denominator) {
//    }

//    int Numerator() const {
//    }

//    int Denominator() const {
//    }
//};

bool TestRational(const Rational& r, int p, int q) {
    if(r.Numerator() == p && r.Denominator() == q)
        return true;
    return false;
}

void TestEmpty() {
    {
        Rational r{};
        Assert(TestRational(r, 0, 1), "TestEmpty");
    }
}

void TestFractionReduction() {
    {
        Rational r{17, 19};
        Assert(TestRational(r, 17, 19), "TestFractionReduction1");
    }
    {
        Rational r{4, 6};
        Assert(TestRational(r, 2, 3), "TestFractionReduction2");
    }
    {
        Rational r{11, 121};
        Assert(TestRational(r, 1, 11), "TestFractionReduction3");
    }
    {
        Rational r{27, 9};
        Assert(TestRational(r, 3, 1), "TestFractionReduction4");
    }
}

void TestSign() {
    {
        Rational r{1, 2};
        Assert(TestRational(r, 1, 2), "TestSign1");
    }
    {
        Rational r{-1, 2};
        Assert(TestRational(r, -1, 2), "TestSign2");
    }
    {
        Rational r{1, -2};
        Assert(TestRational(r, -1, 2), "TestSign3");
    }
    {
        Rational r{-1, -2};
        Assert(TestRational(r, 1, 2), "TestSign4");
    }
}

void TestZero() {
    {
        Rational r{0, 1};
        Assert(TestRational(r, 0, 1), "TestZero1");
    }
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestFractionReduction, "TestFractionReduction");
    runner.RunTest(TestSign, "TestSign");
    runner.RunTest(TestZero, "TestZero");
}

int main() {
    TestAll();

    return 0;
}
