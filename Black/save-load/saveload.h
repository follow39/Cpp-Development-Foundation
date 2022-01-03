#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>

// Serialization

template<typename T>
void Serialize(T pod, std::ostream &out) {
    out.write(reinterpret_cast<const char *>(&pod), sizeof(pod));
}

void Serialize(const std::string &str, std::ostream &out) {
    size_t strSize = str.size();
    out.write(reinterpret_cast<const char *>(&strSize), sizeof(strSize));
    out.write(reinterpret_cast<const char *>(str.data()), strSize);
}

template<typename T>
void Serialize(const std::vector<T> &data, std::ostream &out) {
    size_t dataSize = data.size();
    out.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
    for (const auto &value: data) {
        Serialize(data, out);
    }
}

template<typename T1, typename T2>
void Serialize(const std::map<T1, T2> &data, std::ostream &out) {
    size_t dataSize = data.size();
    out.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
    for (const auto&[key, value]: data) {
        Serialize(key, out);
        Serialize(value, out);
    }
}


// Deserialization

template<typename T>
void Deserialize(std::istream &in, T &pod) {
    in.read(reinterpret_cast<char *>(&pod), sizeof(pod));
}

void Deserialize(std::istream &in, std::string &str) {
    size_t strSize;
    in.read(reinterpret_cast<char *>(&strSize), sizeof(strSize));
    str.resize(strSize);
    in.read(reinterpret_cast<char *>(str.data()), strSize);
}

template<typename T>
void Deserialize(std::istream &in, std::vector<T> &data) {
    size_t dataSize;
    in.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
    data.resize(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        Deserialize(in, data[i]);
    }
}

template<typename T1, typename T2>
void Deserialize(std::istream &in, std::map<T1, T2> &data) {
    size_t dataSize;
    in.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
    for (size_t i = 0; i < dataSize; ++i) {
        T1 key;
        T2 value;
        Deserialize(in, key);
        Deserialize(in, value);
        data.emplace(key, value);
    }
}