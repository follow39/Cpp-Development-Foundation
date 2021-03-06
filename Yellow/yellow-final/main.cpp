#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

#include "database.h"
#include "date.h"
#include "node.h"
#include "condition_parser.h"
#include "test_runner.h"
#include "test_db.h"

using namespace std;

string ParseEvent(istream& is) {
    string temp;
    is >> ws;
    getline(is, temp);
    return temp;
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);
        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

string GenerateDateString(const int year, const int month, const int day) {
    return to_string(year) + "-"s + to_string(month) + "-"s + to_string(day);
}

void TestParseDate() {
    {
        int year = 0;
        int month = 1;
        int day = 1;
        istringstream is(GenerateDateString(year, month, day));
        AssertEqual(ParseDate(is), Date{year, month, day}, is.str());
    }
    {
        int year = -34;
        int month = 5;
        int day = 13;
        istringstream is(GenerateDateString(year, month, day));
        AssertEqual(ParseDate(is), Date{year, month, day}, is.str());
    }
    {
        int year = 1999;
        int month = 2;
        int day = 5;
        istringstream is(GenerateDateString(year, month, day));
        AssertEqual(ParseDate(is), Date{year, month, day}, is.str());
    }
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    auto t1 = std::chrono::high_resolution_clock::now();
    TestRunner tr;
    tr.RunTest(TestParseDate, "TestParseDate");
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestEmptyNode, "Test 2 from Coursera");
    tr.RunTest(TestDbAdd, "Test 3(1) from Coursera");
    tr.RunTest(TestDbFind, "Test 3(2) from Coursera");
    tr.RunTest(TestDbLast, "Test 3(3) from Coursera");
    tr.RunTest(TestDbRemoveIf, "Test 3(4) from Coursera");
    tr.RunTest(TestInsertionOrder, "Order of withdrawal test");
    tr.RunTest(TestsMyCustom, "My tests");
    tr.RunTest(TestDatabase, "Test database from GitHub");
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << endl;
}
