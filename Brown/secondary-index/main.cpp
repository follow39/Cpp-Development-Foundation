#include "test_runner.h"

#include <iostream>
#include <map>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;

    bool operator==(const Record &other) {
        return tie(id, title, user, timestamp, karma) ==
               tie(other.id, other.title, other.user, other.timestamp, other.karma);
    }

    bool operator!=(const Record &other) {
        return tie(id, title, user, timestamp, karma) !=
               tie(other.id, other.title, other.user, other.timestamp, other.karma);
    }
};

// Реализуйте этот класс
class Database {
public:
    struct SecondaryIt {
        list<Record>::iterator it_records;
        multimap<int, list<Record>::iterator>::iterator it_timestamp;
        multimap<int, list<Record>::iterator>::iterator it_karma;
        multimap<string, list<Record>::iterator>::iterator it_user;
    };

    bool Put(const Record &record) {
        if (main_map.find(record.id) == main_map.end()) {
            records.push_front(record);
            auto it_records = records.begin();
            auto it_timestamp = timestamp_map.insert({record.timestamp, it_records});
            auto it_karma = karma_map.insert({record.karma, it_records});
            auto it_user = user_map.insert({record.user, it_records});
            main_map.insert({record.id, {it_records, it_timestamp, it_karma, it_user}});
            return true;
        }
        return false;
    }

    const Record *GetById(const string &id) const {
        if (main_map.find(id) != main_map.end()) {
            return &(*main_map.at(id).it_records);
        }
        return nullptr;
    }

    bool Erase(const string &id) {
        if (main_map.find(id) != main_map.end()) {
            SecondaryIt it = main_map.at(id);
            records.erase(it.it_records);
            timestamp_map.erase(it.it_timestamp);
            karma_map.erase(it.it_karma);
            user_map.erase(it.it_user);
            main_map.erase(id);
            return true;
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
        const auto[it_first, it_last] = user_map.equal_range(user);
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

    list<Record> records;
    multimap<int, list<Record>::iterator> timestamp_map;
    multimap<int, list<Record>::iterator> karma_map;
    multimap<string, list<Record>::iterator> user_map;
//    unordered_map<string, pair<Record, SecondaryIt>> id_map;
    unordered_map<string, SecondaryIt> main_map;
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
