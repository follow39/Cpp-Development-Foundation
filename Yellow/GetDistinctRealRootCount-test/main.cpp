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

int GetDistinctRealRootCount(double a, double b, double c) {
    return 0;
}

bool TestGetDistinctRealRootCount(double a, double b, double c, int expected) {
    if(GetDistinctRealRootCount(a, b, c) == expected)
        return true;
    return false;
}

void TestZero() {
    Assert(TestGetDistinctRealRootCount(1, 1, 1, 0), "1_1_1");
    Assert(TestGetDistinctRealRootCount(19, 15, 31, 0), "19_15_31");
    Assert(TestGetDistinctRealRootCount(269, -78, 593, 0), "269_-78_593");
    Assert(TestGetDistinctRealRootCount(26.59, -0.983, 38.2, 0), "26.59_-0.983_38.2");
    Assert(TestGetDistinctRealRootCount(-26.59, 0.983, -38.2, 0), "-26.59_0.983_-38.2");
}
void TestOne() {
    Assert(TestGetDistinctRealRootCount(1, 2, 1, 1), "1_2_1");
    Assert(TestGetDistinctRealRootCount(64, 32, 4, 1), "64_32_4");
}
void TestTwo() {
    Assert(TestGetDistinctRealRootCount(1, 3, 1, 2), "1_3_1");
    Assert(TestGetDistinctRealRootCount(47, 38, 7, 2), "47_38_7");
    Assert(TestGetDistinctRealRootCount(5.185, 9.4788, 593, 2), "5.185_9.4788_-78.1465");
    Assert(TestGetDistinctRealRootCount(-5.185, 47.1864, -78.1465, 2), "-5.185_47.1864_-78.1465");
}
void TestAzero() {
    Assert(TestGetDistinctRealRootCount(0, 1, 1, 1), "0_1_1");
    Assert(TestGetDistinctRealRootCount(0, 8, -13, 1), "0_8_-13");
    Assert(TestGetDistinctRealRootCount(0, -5, 61, 2), "0_-5_61");
    Assert(TestGetDistinctRealRootCount(0, -96, -86, 0), "0_-96_-86");
}
void TestBzero() {
    Assert(TestGetDistinctRealRootCount(1, 0, 1, 0), "1_0_1");
    Assert(TestGetDistinctRealRootCount(15, 0, -39, 2), "15_0_-39");
    Assert(TestGetDistinctRealRootCount(-59, 0, 19, 2), "-59_0_19");
    Assert(TestGetDistinctRealRootCount(-43, 0, -86, 0), "-43_0_-86");
}
void TestCzero() {
    Assert(TestGetDistinctRealRootCount(1, 1, 0, 2), "1_1_0");
    Assert(TestGetDistinctRealRootCount(939, -801, 0, 2), "939_-801_0");
    Assert(TestGetDistinctRealRootCount(3, 56, 0, 2), "3_56_0");
    Assert(TestGetDistinctRealRootCount(19, 2, 0, 2), "19_2_0");
}
void TestABzero() {
    Assert(TestGetDistinctRealRootCount(0, 0, 1, 0), "0_0_1");
}
void TestACzero() {
    Assert(TestGetDistinctRealRootCount(0, 1, 0, 0), "0_1_0");
}
void TestBCzero() {
    Assert(TestGetDistinctRealRootCount(1, 0, 0, 1), "1_0_0");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestZero, "TestZero");
    runner.RunTest(TestOne, "TestOne");
    runner.RunTest(TestTwo, "TestTwo");

    runner.RunTest(TestAzero, "TestAzero");
    runner.RunTest(TestBzero, "TestBzero");
    runner.RunTest(TestCzero, "TestCzero");

    runner.RunTest(TestABzero, "TestABzero");
    runner.RunTest(TestACzero, "TestACzero");
    runner.RunTest(TestBCzero, "TestBCzero");
}

int main() {
    TestAll();

  return 0;
}
