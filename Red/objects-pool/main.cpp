#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;


template <class T>
class ObjectPool {
public:
    T* Allocate() {
        T* result = nullptr;
        if(deallocatePool.size() != 0) {
            result = deallocatePool.front();
            allocatePool.insert(result);
            deallocatePool.pop();
        } else {
            result = new T;
            allocatePool.insert(result);
        }
        return result;
    }
    T* TryAllocate() {
        T* result = nullptr;
        if(deallocatePool.size() != 0) {
            result = deallocatePool.front();
            allocatePool.insert(result);
            deallocatePool.pop();
        }
        return result;
    }

    void Deallocate(T* object) {
        if(allocatePool.count(object) == 0) {
            throw invalid_argument("The argument is not pooled");
        }
        deallocatePool.push(object);
        allocatePool.erase(object);
    }

    ~ObjectPool() {
        for(const auto& ptr : allocatePool) {
            delete ptr;
        }
        allocatePool.clear();
        while(!deallocatePool.empty()) {
            delete deallocatePool.front();
            deallocatePool.pop();
        }
    }

private:
    set<T*> allocatePool;
    queue<T*> deallocatePool;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
