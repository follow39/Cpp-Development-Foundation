#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    int r = 0;
    long w = 0;
    long h = 0;
    long d = 0;
    long long sum = 0;

    cin >> n >> r;

    while(n-- > 0)
    {
        cin >> w >> h >> d;

        sum += r * w * h * d;
    }

    cout << sum;

    return 0;
}
