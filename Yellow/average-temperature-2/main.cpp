#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long> vec;
    vector<long> vecGavg;
    long n = 0;
    long temp = 0;
    long sum = 0;
    cin >> n;

    while(n-- > 0) {
        cin >> temp;
        vec.push_back(temp);
        sum += temp;
    }

    long avg = sum / static_cast<long>(vec.size());

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
