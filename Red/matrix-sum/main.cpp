#include "test_runner.h"
#include <iostream>
#include <vector>
#include <future>
#include <numeric>
#include <iterator>
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
template <typename ContainerOfVectors>
int64_t CalculateSingleThread(const ContainerOfVectors& page) {
    int64_t result = 0;
    for(auto& row : page) {
        result += accumulate(row.begin(), row.end(), 0);
    }
    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    int64_t result = 0;

    for(auto& page : Paginate(matrix, min(matrix.size(), static_cast<size_t>(10)))) {
        futures.push_back(async([&page] { return CalculateSingleThread(page); }));
//        result += CalculateSingleThread(page);
    }

    for(auto& x : futures) {
        result += x.get();
    }
    return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
