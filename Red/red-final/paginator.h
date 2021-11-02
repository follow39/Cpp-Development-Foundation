#pragma once

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename Iterator>
class PaginatorPage {
public:
    PaginatorPage(Iterator begin, Iterator end, size_t size)
        : page_size(min(static_cast<size_t>(end - begin), size)),
          first(begin),
          last(begin + page_size) {}
    Iterator begin() {
        return first;
    }
    const Iterator begin() const {
        return first;
    }
    Iterator end() {
        return last;
    }
    const Iterator end() const {
        return last;
    }
    size_t size() const {
        return page_size;
    }

private:
    size_t page_size;
    Iterator first;
    Iterator last;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t size) {
        for(auto it = begin; it != end; it+=size) {
            pages.push_back({it, end, size});
            if(pages.back().size() < size) {
                break;
            }
        }
    }
    auto begin() const {
        return pages.begin();
    }
    auto end() const {
        return pages.end();
    }
    size_t size() const {
        return pages.size();
    }

private:
    vector<PaginatorPage<Iterator>> pages;
    size_t page_size;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{c.begin(), c.end(), page_size};
}

