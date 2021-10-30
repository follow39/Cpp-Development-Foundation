#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename T>
class PriorityCollection {
public:
    using Id = time_point<steady_clock>;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        Id id = steady_clock::now();
        object_collection[id] = {move(object), 0};
        priority_collection[0].insert(id);
        return id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        for(auto it = range_begin; it != range_end; ++it) {
            *ids_begin++ = Add(move(*it));;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return object_collection.count(id);
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return object_collection.at(id);
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        priority_collection[object_collection[id].second].erase(id);
        if(priority_collection[object_collection[id].second].empty()) {
            priority_collection.erase(object_collection[id].second);
        }
        ++object_collection[id].second;
        priority_collection[object_collection[id].second].insert(id);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        Id id = *((priority_collection.rbegin()->second).rbegin());
        return object_collection[id];
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {
        Id id = *priority_collection.rbegin()->second.rbegin();
        priority_collection[object_collection[id].second].erase(id);
        if(priority_collection[object_collection[id].second].empty()) {
            priority_collection.erase(object_collection[id].second);
        }
        auto temp = move(object_collection[id]);
        object_collection.erase(id);
        return move(temp);
    }


private:
    // Приватные поля и методы
    map<Id, pair<T, int>> object_collection;
    map<int, set<Id>> priority_collection;
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

void TestGoodForMe() {
    const int COUNT = 3;
    PriorityCollection<StringNonCopyable> strings;

    vector<PriorityCollection<StringNonCopyable>::Id> ids;
    for (int i = 0; i < COUNT; ++i) {
        ids.push_back(strings.Add(StringNonCopyable(1, 'a' + i)));
    }
    strings.Promote(ids[0]);
}

void TestId5() {
    PriorityCollection<StringNonCopyable> strings;
    list<StringNonCopyable> items;
    for (int i = 0; i < 10; ++i) {
        items.push_back(StringNonCopyable(1, 'a' + i));
    }
    vector<PriorityCollection<StringNonCopyable>::Id> ids;
    strings.Add(begin(items), end(items), back_inserter(ids));
    strings.Promote(ids[5]);
    ASSERT_EQUAL(strings.IsValid(ids[5]), true);
    pair<StringNonCopyable, int> result = strings.PopMax();
    ASSERT_EQUAL(result.first, "f");
    ASSERT_EQUAL(result.second, 1);
    ASSERT_EQUAL(strings.IsValid(ids[5]), false);

    ids.push_back(strings.Add(move(result.first)));
    ASSERT_EQUAL(strings.IsValid(ids[5]), true); // Старый id стал валиден
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    RUN_TEST(tr, TestGoodForMe);
    RUN_TEST(tr, TestId5);
    return 0;
}
