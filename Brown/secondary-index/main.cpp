#include "test_runner.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

// Реализуйте этот класс
class Database {
public:
    bool Put(const Record &record) {
        auto temp = id_map.insert({record.id, record});
        if (temp.second) {
            timestamp_map.insert({record.timestamp, &temp.first->second});
            karma_map.insert({record.karma, &temp.first->second});
            user_map.insert({record.user, &temp.first->second});
            return true;
        }
        return false;
    }

    const Record *GetById(const string &id) const {
        auto it = id_map.find(id);
        if (it != id_map.end()) {
            return &it->second;
        }
        return nullptr;
    }

    bool Erase(const string &id) {
        const auto it = id_map.find(id);
        if (it != id_map.end()) {
            auto it_timestamp_remove = timestamp_map.lower_bound(it->second.timestamp);
            while (it_timestamp_remove->second != &it->second) {
                ++it_timestamp_remove;
            }
            timestamp_map.erase(it_timestamp_remove);
            auto it_karma_remove = karma_map.lower_bound(it->second.timestamp);
            while (it_karma_remove->second != &it->second) {
                ++it_karma_remove;
            }
            karma_map.erase(it_karma_remove);
            auto it_user_remove = user_map.lower_bound(it->second.user);
            while (it_user_remove->second != &it->second) {
                ++it_user_remove;
            }
            user_map.erase(it_user_remove);
            id_map.erase(it);
        }
        return false;
    }

    template<typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        const auto it_first = timestamp_map.lower_bound(low);
        const auto it_last = timestamp_map.upper_bound(high);
        RangeBy(it_first, it_last, callback);
    }

    template<typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        const auto it_first = karma_map.lower_bound(low);
        const auto it_last = karma_map.upper_bound(high);
        RangeBy(it_first, it_last, callback);
    }

    template<typename Callback>
    void AllByUser(const string &user, Callback callback) const {
        const auto it_first = user_map.lower_bound(user);
        const auto it_last = user_map.upper_bound(user);
        RangeBy(it_first, it_last, callback);
    }

private:
    template<typename InputIt, typename Callback>
    void RangeBy(const InputIt first, const InputIt last, Callback callback) const {
        auto it = first;
        while (it != last && callback(*(it->second))) {
            ++it;
        }
    }

    multimap<int, Record *> timestamp_map;
    multimap<int, Record *> karma_map;
    multimap<string, Record *> user_map;
    map<string, Record> id_map;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record &) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record &) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
