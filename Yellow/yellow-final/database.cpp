#include "database.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if(event.empty())
        return;
    db[date].emplace(event);
}
bool Database::DeleteEvent(const Date& date, const string& event) {
    bool result = (db[date].count(event) > 0);
    db[date].erase(event);
    return result;
}
int Database::DeleteDate(const Date& date) {
    int result = db[date].size();
    db.erase(date);
    return result;
}

set<string> Database::Find(const Date& date) const {
    if(db.count(date) > 0) {
        return db.at(date);
    }
    return set<string>{};
}

std::ostream& Database::Print(std::ostream& os) const {
    for(auto& [date, events] : db) {
        for(const auto& event : events) {
            os << date << ' ' << event << endl;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, dBase data) {
    return os;
}

std::ostream& operator<<(std::ostream& os, std::pair<Date, std::set<std::string>> data) {
    return os;
}

std::ostream& operator<<(std::ostream& os, events data) {
    return os;
}
