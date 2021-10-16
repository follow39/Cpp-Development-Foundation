#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
//#include "merge-sort-2.h"
//#include "merge-sort-3.h"

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
    merge(temp.begin(), temp.end(), mid2, vec.end(), range_begin);
}

int main() {
    vector<int> v2 = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v2), end(v2));
    for (int x : v2) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> v3 = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v3), end(v3));
    for (int x : v3) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
