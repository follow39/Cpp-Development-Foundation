#include "database.h"
#include <exception>
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if(db.empty()) {
        db.push_back(DBaseUnit{date, {event}});
        return;
    }

    auto it_lower = lower_bound(db.begin(), db.end(), date, [](const auto& unit, const Date& date) {
        return unit.first < date;
    });
    const auto it_upper = upper_bound(it_lower, db.end(), date, [](const Date& date, const auto& unit) {
        return unit.first > date;
    });

    if(it_lower != db.end() && it_lower->first == date) {
        const auto it_find = find_if(it_lower, db.end(), [event](const DBaseUnit unit) {
            return unit.second == event;
        });
        if(it_find != db.end()) {
            return;
        }
    }

    db.insert(it_upper, DBaseUnit{date, {event}});
}

DBaseUnit Database::Last(const Date& date) const {
    if(db.empty() || date < db.front().first) {
        throw invalid_argument("No entries");
    }
    auto it = lower_bound(db.rbegin(), db.rend(), date, [](const auto& lhs, const Date& date) {
        return lhs.first > date;
    });
    return DBaseUnit{it->first, {it->second}};
}

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
    if(db.empty()) {
        return 0;
    }
    int cnt = 0;
    const auto it = remove_if(db.begin(), db.end(), [predicate](const DBaseUnit& unit) {
        return predicate(unit.first, unit.second);
    });

    cnt = db.end() - it;
    db.erase(it, db.end());

    return cnt;
}

DBase Database::FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const {
    if(db.empty()) {
        return {};
    }

    DBase result;
    copy_if(db.begin(), db.end(), back_inserter(result), [predicate](const DBaseUnit& unit) {
        return predicate(unit.first, unit.second);
    });

    return result;
}


void Database::Print(std::ostream& os) const {
    os << db;
}

std::ostream& operator<<(std::ostream& os, const DBase& data) {
    for(const auto& i : data) {
        os << i << endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const DBaseUnit& data) {
    os << data.first << ' ' << data.second;
    return os;
}
