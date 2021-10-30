#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if((range_end - range_begin) < 2)
        return;
    vector<typename  RandomIt::value_type> vec(make_move_iterator(range_begin), make_move_iterator(range_end));
    RandomIt mid = vec.begin() + vec.size()/2;
    MergeSort(vec.begin(), mid);
    MergeSort(mid, vec.end());
    merge(vec.begin(), mid, make_move_iterator(mid),
          make_move_iterator(vec.end()), range_begin);
//    merge(make_move_iterator(vec.begin()), make_move_iterator(mid), make_move_iterator(mid),
//          make_move_iterator(vec.end()), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
