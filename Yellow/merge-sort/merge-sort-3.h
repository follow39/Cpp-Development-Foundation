#ifndef MERGESORT3_H
#define MERGESORT3_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if((range_end - range_begin) < 2)
        return;
    vector<typename  RandomIt::value_type> vec(range_begin, range_end);
    vector<typename  RandomIt::value_type> temp;
    RandomIt mid1 = vec.begin() + vec.size()/3;
    RandomIt mid2 = vec.begin() + vec.size()*2/3;
    MergeSort(vec.begin(), mid1);
    MergeSort(mid1, mid2);
    MergeSort(mid2, vec.end());
    merge(vec.begin(), mid1, mid1, mid2, back_inserter(temp));
    merge(mid2, vec.end(), temp.begin(), temp.end(), range_begin);
}

#endif // MERGESORT3_H
