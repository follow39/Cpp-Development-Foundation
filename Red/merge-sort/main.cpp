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
    vector<typename  RandomIt::value_type> temp;
    RandomIt mid1 = vec.begin() + vec.size()/3;
    RandomIt mid2 = vec.begin() + vec.size()*2/3;
    MergeSort(vec.begin(), mid1);
    MergeSort(mid1, mid2);
    MergeSort(mid2, vec.end());
    merge(make_move_iterator(vec.begin()), make_move_iterator(mid1),
          make_move_iterator(mid1), make_move_iterator(mid2), back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()),
          make_move_iterator(mid2), make_move_iterator(vec.end()), range_begin);
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
