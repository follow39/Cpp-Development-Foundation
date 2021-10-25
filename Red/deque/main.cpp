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

    }
    const T& operator[](size_t index) const {

    }
    T& At(size_t index) {
        if(index >= Size()) {
            throw out_of_range("out of range");
        }

    }
    const T& At(size_t index) const {
        if(index >= Size()) {
            throw out_of_range("out of range");
        }

    }
    T& Front(size_t index) {
        return vec_front.back();
    }
    const T& Front(size_t index) const {
        return vec_front.back();
    }
    T& Back(size_t index) {
        return vec_back.back();
    }
    const T& Back(size_t index) const {
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
    cout << "Hello World!" << endl;
    return 0;
}
