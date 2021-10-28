#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
    SimpleVector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    explicit SimpleVector(size_t new_size) {
        data = new T[new_size];
        size = new_size;
        capacity = new_size;
    }
    ~SimpleVector() {
        delete [] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() {
        return &data[0];
    }
    T* end() {
        return &data[size];
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if(capacity == 0) {
            data = new T[1];
            capacity = 1;
        }
        if(size == capacity) {
            capacity *= 2;
            T* new_data = new T[capacity];
            for(size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete [] data;
            data = new_data;
        }
        data[size] = value;
        ++size;
    }

private:
    T* data;
    size_t size;
    size_t capacity;
};
