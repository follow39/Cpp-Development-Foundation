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
    auto it = db_vector.upper_bound(date);
    --it;
    return DBaseUnit{it->first, {it->second.back()}};
}

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
    if(db_vector.empty()) {
        return 0;
    }

    int cnt = 0;
    vector<Date> erase_vector;

    for(auto& [key, value] : db_vector) {
        auto& k = key;
        const auto it_remove = stable_partition(value.begin(), value.end(), [&k, predicate](const string& event) {
            return !predicate(k, event);
        });

        if(it_remove == value.end()) {
            continue;
        }

        cnt += value.end() - it_remove;

        if(it_remove == value.begin()) {
            erase_vector.push_back(key);
            continue;
        }

        for(auto it = it_remove; it != value.end(); ++it) {
            db_set[key].erase(*it);
        }

        value.erase(it_remove, value.end());
        //        db_set[key] = set<string>(value.begin(), value.end());
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
