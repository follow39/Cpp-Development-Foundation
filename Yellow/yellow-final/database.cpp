#include "database.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if(db.empty()) {
        db[date].first.push_back(event);
        db[date].second.emplace(event);
    } else if(db[date].second.insert(event).second) {
        db[date].first.push_back(event);
    }
}

Entry Database::Last(const Date& date) const {
    if(db.empty() || date < db.begin()->first) {
        throw invalid_argument("No entries");
    }
    auto it = db.upper_bound(date);
    --it;
    return Entry{it->first, {it->second.first.back()}};
}

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
    if(db.empty()) {
        return 0;
    }
    int cnt = 0;
    auto it = db.begin();

    while(it != db.end()) {
        auto& key = it->first;
        auto& db_vector = it->second.first;
        auto& db_set = it->second.second;

        const auto it_border = stable_partition(db_vector.begin(), db_vector.end(), [&key, predicate](const string& event) {
            return !predicate(key, event);
        });
        if(it_border != db_vector.end()) {
            cnt += db_vector.end() - it_border;
            if(it_border == db_vector.begin()) {
                auto it_erase = it;
                ++it;
                db.erase(it_erase);
                continue;
            }

            for(auto it_remove = it_border; it_remove != db_vector.end(); ++it_remove) {
                db_set.erase(*it_remove);
            }
            db_vector.erase(it_border, db_vector.end());
        }
        ++it;
    }

    return cnt;
}

EntryVector Database::FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const {
    if(db.empty()) {
        return {};
    }
    EntryVector result;
    for(const auto& [key, value] : db) {
        for(const auto& e : value.first) {
            if(predicate(key, e)) {
                result.push_back(Entry{key, e});
            }
        }
    }
    return result;
}


void Database::Print(std::ostream& os) const {
    for(const auto& [key, value] : db) {
        for(const auto& e : value.first) {
            os << Entry{key, e} << endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const EntryVector& data) {
    for(const auto& i : data) {
        os << i << endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Entry& data) {
    os << data.first << ' ' << data.second;
    return os;
}
