#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;
    vector<int> vecGavg;
    int n = 0;
    int temp = 0;
    int sum = 0;
    cin >> n;

    while(n-- > 0) {
        cin >> temp;
        vec.push_back(temp);
        sum += temp;
    }

    int avg = sum / static_cast<int>(vec.size());

    for(size_t i = 0; i < vec.size(); ++i) {
        if(vec[i] > avg) {
            vecGavg.push_back(i);
        }
    }
    cout << vecGavg.size() << endl;

    for(const auto& i : vecGavg) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}
