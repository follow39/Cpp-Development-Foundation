#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "merge-sort-2.h"
#include "merge-sort-3.h"

using namespace std;


int main() {
    vector<int> v2 = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort2(begin(v2), end(v2));
    for (int x : v2) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> v3 = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort3(begin(v3), end(v3));
    for (int x : v3) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
