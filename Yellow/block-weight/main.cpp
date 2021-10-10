#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    int r = 0;
    int64_t w = 0;
    int64_t h = 0;
    int64_t d = 0;
    unsigned long long sum = 0;

    cin >> n >> r;

    while(n-- > 0)
    {
        cin >> w >> h >> d;

        sum += r * w * h * d;
    }

    cout << sum;

    return 0;
}
