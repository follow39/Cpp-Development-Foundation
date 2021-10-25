#include <iostream>
#include <vector>
#include <exception>

using namespace std;

template <typename T>
class Deque {
public:
    Deque() {}
    bool Empty() const {
        return vec_front.empty() && vec_back.empty();
    }
    size_t Size() const {
        return vec_front.size() + vec_back.size();
    }

    T& operator[](size_t index) {
        return Get(index);
    }
    const T& operator[](size_t index) const {
        return Get(index);
    }

    T& At(size_t index) {
        if(index >= Size()) {
            throw out_of_range("out of range");
        }
        return Get(index);
    }
    const T& At(size_t index) const {
        if(index >= Size()) {
            throw out_of_range("out of range");
        }
        return Get(index);
    }

    T& Front() {
        if(vec_front.empty()) {
            if(!vec_back.empty()) {
                return vec_back.front();
            }
        }
        return vec_front.back();
    }
    const T& Front() const {
        if(vec_front.empty()) {
            if(!vec_back.empty()) {
                return vec_back.front();
            }
        }
        return vec_front.back();
    }

    T& Back() {
        if(vec_back.empty()) {
            if(!vec_front.empty()) {
                return vec_front.front();
            }
        }
        return vec_back.back();
    }
    const T& Back() const {
        if(vec_back.empty()) {
            if(!vec_front.empty()) {
                return vec_front.front();
            }
        }
        return vec_back.back();
    }

    void PushFront(const T& value) {
        vec_front.push_back(value);
    }
    void PushBack(const T& value) {
        vec_back.push_back(value);
    }

private:
    T& Get(size_t index) {
        if(index < vec_front.size()) {
            return vec_front[vec_front.size() - index - 1];
        }
        return vec_back[index - vec_front.size()];
    }
    const T& Get(size_t index) const {
        if(index < vec_front.size()) {
            return vec_front[vec_front.size() - index - 1];
        }
        return vec_back[index - vec_front.size()];
    }
    vector<T> vec_front;
    vector<T> vec_back;
};


void foo(Deque<int> const& d) {
    for (int i = 0; i < d.Size(); ++i) {
        printf("%d ", d.At(i));

    }
}
int main() {
    Deque<int> deque;
    deque.PushFront(1);
    deque.PushBack(2);
    foo(deque);
}
