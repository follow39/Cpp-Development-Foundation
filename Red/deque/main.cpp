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
        if(index < vec_front.size()) {
            return vec_front[vec_front.size() - index];
        }
        return vec_back[index - vec_front.size()];
    }
    const T& operator[](size_t index) const {
        if(index < vec_front.size()) {
            return vec_front[vec_front.size() - index];
        }
        return vec_back[index - vec_front.size()];
    }
    T& At(size_t index) {
        if(index < vec_front.size()) {
            return vec_front.at(vec_front.size() - index);
        }
        return vec_back.at(index - vec_front.size());
    }
    const T& At(size_t index) const {
        if(index < vec_front.size()) {
            return vec_front.at(vec_front.size() - index);
        }
        return vec_back.at(index - vec_front.size());
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
    vector<T> vec_front;
    vector<T> vec_back;
};



int main()
{
    return 0;
}
