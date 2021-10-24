#include "database.h"
#include <exception>
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if(db_set.empty() || db_set[date].count(event) == 0) {
        db_set[date].emplace(event);
        db_vector[date].push_back(event);
    }
}

DBaseUnit Database::Last(const Date& date) const {
    if(db_vector.empty() || date < db_vector.begin()->first) {
        throw invalid_argument("No entries");
    }
    auto it = lower_bound(db_vector.rbegin(), db_vector.rend(), date, [](const auto& lhs, const Date& date) {
        return lhs.first > date;
    });
    return DBaseUnit{it->first, {it->second.back()}};
}

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
    if(db_vector.empty()) {
        return 0;
    }

    int cnt = 0;
    vector<Date> erase_vector;

    for(auto& [key, value] : db_vector) {
        if(!predicate(key, "")) {
            continue;
        }

        auto k = key;
        const auto it_remove = remove_if(value.begin(), value.end(), [k, predicate](const auto& event) {
            return predicate(k, event);
        });

        if(it_remove == value.end()) {
            continue;
        }

        if(it_remove == value.begin()) {
            cnt += db_vector[key].size();
            erase_vector.push_back(key);
            continue;
        }

        for(auto it = it_remove; it != value.end(); ++it) {
            db_set[key].erase(*it);
            ++cnt;
        }
        value.erase(it_remove);
    }

    for(const auto& key : erase_vector) {
        db_vector.erase(key);
        db_set.erase(key);
    }


    return cnt;
}

DBase Database::FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const {
    if(db_vector.empty()) {
        return {};
    }

    DBase result;
    //    copy_if(db.begin(), db.end(), back_inserter(result), [predicate](const DBaseUnit& unit) {
    //        return predicate(unit.first, unit.second);
    //    });
    for(const auto& [key, value] : db_vector) {
        for(const auto& e : value) {
            if(predicate(key, e)) {
                result.push_back(DBaseUnit{key, e});
            }
        }
    }
    return result;
}


void Database::Print(std::ostream& os) const {
    for(const auto& [key, value] : db_vector) {
        for(const auto& e : value) {
            os << DBaseUnit{key, e} << endl;
        }
    }
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
