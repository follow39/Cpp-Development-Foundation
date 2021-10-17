#include <iostream>
#include <set>
#include <iterator>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
        int border) {
    set<int>::const_iterator result = numbers.begin();
    bool f = false;

    for(auto it = numbers.begin(); it != numbers.end(); ++it) {
        if(abs(*it - border) < abs(*result - border)) {
            result = it;
            f = true;
        } else if(f) {
            break;
        }
    }

    return result;
}


int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
