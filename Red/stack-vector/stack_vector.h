#pragma once

#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if(a_size > N) {
            throw invalid_argument("Size > N");
        }
        size = a_size;
    }

    T& operator[](size_t index) {
        return data[index];
    }
    const T& operator[](size_t index) const {
        return data[index];
    }

    T* begin() {
        return &data[0];
    }
    T* end() {
        return &data[size];
    }
    const T* begin() const {
        return &data[0];
    }
    const T* end() const {
        return &data[size];
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return N;
    }

    void PushBack(const T& value) {
        if(size == N) {
            throw overflow_error("overflow");
        }
        data[size] = value;
        ++size;
    }
    T PopBack() {
        if(size == 0) {
            throw underflow_error("underflow");
        }
        --size;
        return data[size];
    }

private:
    T data[N];
    size_t size;
};
