#ifndef MERGESORT2_H
#define MERGESORT2_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort2(RandomIt range_begin, RandomIt range_end) {
    if((range_end - range_begin) < 2)
        return;
    vector<typename  RandomIt::value_type> vec(range_begin, range_end);
    RandomIt mid = vec.begin() + vec.size()/2;
    MergeSort2(vec.begin(), mid);
    MergeSort2(mid, vec.end());
    merge(vec.begin(), mid, mid, vec.end(), range_begin);
}

#endif // MERGESORT2_H
