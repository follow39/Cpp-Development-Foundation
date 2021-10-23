#include "database.h"
#include <exception>
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if(db.empty()) {
        db.push_back(make_shared<DBaseUnit>(DBaseUnit{date, {event}}));
        return;
    }

    const auto it = lower_bound(db.begin(), db.end(), date, [](const auto& lhs, const Date& date) {
        return (*lhs).first < date;
    });

    if(it == db.end()) {
        db.insert(it, make_shared<DBaseUnit>(DBaseUnit{date, {event}}));
    } else if((*it)->first == date) {
        (*it)->second.push_back(event);
    } else {
        db.insert(it, make_shared<DBaseUnit>(DBaseUnit{date, {event}}));
    }
}

DBaseUnit Database::Last(const Date& date) const {
    if(db.empty() || date < db.front()->first) {
        throw invalid_argument("No entries");
    }
    auto it = lower_bound(db.rbegin(), db.rend(), date, [](const auto& lhs, const Date& date) {
        return (*lhs).first > date;
    });
    return DBaseUnit{(*it)->first, {(*it)->second.back()}};
}

void Database::Print(std::ostream& os) const {
    os << db;
}

std::ostream& operator<<(std::ostream& os, const DBase& data) {
    for(const auto& i : data) {
        os << *i;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const DBaseUnit& data) {
    for(const auto& e : data.second) {
        os << data.first << ' ' << e << endl;
    }
    return os;
}
