#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <system_error>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class Date {
public:
    Date() {
        year = 0;
        month = 1;
        day = 1;
    }
    Date(int new_year, int new_month, int new_day) {
        if(new_month < 1 || new_month > 12) {
            string what("Month value is invalid: " + to_string(new_month));
            throw runtime_error(what);
        }
        if(new_day < 1 || new_day > 31) {
            string what("Day value is invalid: " + to_string(new_day));
            throw runtime_error(what);
        }
        year = new_year;
        month = new_month;
        day = new_day;
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
private:
    int year;
    int month;
    int day;
};

bool operator==(const Date& lhs, const Date& rhs)
{
    if(lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() == rhs.GetMonth() &&
            lhs.GetDay() == rhs.GetDay()) {
        return true;
    }
    return false;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if(lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    } else if(lhs.GetMonth() != rhs.GetMonth()) {
        return lhs.GetMonth() < rhs.GetMonth();
    } else if(lhs.GetDay() != rhs.GetDay()) {
        return lhs.GetDay() < rhs.GetDay();
    }
    return false;
}

void EnsureNextSymbolAndSkip(stringstream& stream) {
    if (stream.peek() != '-') {
        throw exception();
    }
    stream.ignore(1);
}

stringstream& operator>>(stringstream& stream, Date& date)
{
    string temp;
    stream >> temp;
    stringstream ss(temp);

    int year;
    int month;
    int day;
    char c1;
    char c2;

    try {
        if((ss >> year >> c1 >> month >> c2 >> day) && ss.eof()) {
            if(c1 != '-' || c2 != '-') {
                throw exception();
            }
        }
        else {
            throw exception();
        }
    }  catch (exception& ex) {
        string what("Wrong date format: "s + temp);
        throw runtime_error(what);
    }

    date = Date{year, month, day};

    return stream;
}

ostream& operator<<(ostream& stream, const Date& date)
{
    stream << setw(4) << setfill('0') << date.GetYear() << '-' <<
              setw(2) << setfill('0') << date.GetMonth() << '-' <<
              setw(2) << setfill('0') << date.GetDay();

    return stream;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        if(event.empty())
            return;
        db[date].emplace(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        bool result = (db[date].count(event) > 0);
        db[date].erase(event);
        return result;
    }
    int  DeleteDate(const Date& date) {
        int result = db[date].size();
        db.erase(date);
        return result;
    }

    set<string> Find(const Date& date) const {
        if(db.count(date) > 0) {
            return db.at(date);
        }
        return set<string>{};
    }

    void Print() const {
        for(auto& [date, events] : db) {
            for(const auto& event : events) {
                cout << date << ' ' << event << endl;
            }
        }
    }
private:
    map<Date, set<string>> db;
};


int main() {
    Database db;
    stringstream ss;
    string cmd;
    Date date;
    string event;

    string command;
    while (getline(cin, command)) {
        if(command.empty())
            continue;

        event = "";
        ss.clear();
        ss << command;
        try {
            ss >> cmd;
            if(cmd == "Add") {
                ss >> date >> event;
                db.AddEvent(date, event);
            } else if(cmd == "Del") {
                ss >> date >> event;
                if(event.empty()) {
                    int n = db.DeleteDate(date);
                    cout << "Deleted " << n << " events" << endl;
                } else {
                    bool del = db.DeleteEvent(date, event);
                    if(del) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if(cmd == "Find") {
                ss >> date;
                set events = db.Find(date);
                for(const auto& event : events) {
                    cout << event << endl;
                }
            } else if(cmd == "Print") {
                db.Print();
            } else {
                string what("Unknown command: " + cmd);
                throw runtime_error(what);
            }
        }  catch (exception& ex) {
            cout << ex.what() << endl;
            return 0;
        }
    }

    return 0;
}
