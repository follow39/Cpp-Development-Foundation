#include "test_runner.h"
#include "profile.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>
#include <deque>
#include <iostream>

using namespace std;


template <typename T, typename RandomIt>
void func(T& container, RandomIt& it, size_t step_size) {
    while(step_size > 0) {
        if(it == container.end()) {
            it = container.begin();
        }
        ++it;
        --step_size;
    }
    if(it == container.end()) {
        it = container.begin();
    }
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    if(last - first < 2) {
        return;
    }
    list<typename RandomIt::value_type> pool;
    for(auto it = first; it != last; ++it) {
        pool.push_back(move(*it));
    }
    auto current_it = pool.begin();
    while (!pool.empty()) {
//        cerr << *current_it << endl;
        *(first++) = move(*current_it);
        ++current_it;
        pool.erase(prev(current_it));
        if(pool.empty()) {
            break;
        }
        func(pool, current_it, step_size-1);
    }
}

vector<int> MakeTestVector(int n) {
    vector<int> numbers(n);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector(10);
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}


struct NoncopyableInt {
    int value;

    NoncopyableInt(int value) : value(value) {}

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main() {
    LOG_DURATION("Total");
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    vector<int> numbers = MakeTestVector(100000);
    MakeJosephusPermutation(begin(numbers), end(numbers), 100);
    return 0;
}
