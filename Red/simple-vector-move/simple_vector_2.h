#pragma once

#include <cstdlib>
#include <algorithm>
#include <iterator>


template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t new_size)
        : data(new T[new_size]),
          size(new_size),
          capacity(new_size) {}
    explicit SimpleVector(const SimpleVector& other) = delete;
    explicit SimpleVector(SimpleVector&& other) {
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = other.capacity = 0;
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
        return capacity;
    }
    void PushBack(T value) {
        if(capacity == 0) {
            data = new T[1];
            capacity = 1;
        }
        if(size == capacity) {
            capacity *= 2;
            T* new_data = new T[capacity];
            std::copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), new_data);
            delete [] data;
            data = new_data;
        }
        data[size] = std::move(value);
        ++size;
    }
    void operator=(const SimpleVector& other) = delete;
    void operator=(SimpleVector&& other) {
        delete [] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = other.capacity = 0;
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

