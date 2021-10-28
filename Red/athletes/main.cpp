#include <iostream>
#include <list>
#include <map>

using namespace std;

int main()
{
    list<int> l;
    map<int, list<int>::iterator> m;
    int n_current = 0;
    int n_prev = 0;

    int q = 0;
    cin >> q;
    while(q-- > 0) {
        cin >> n_current >> n_prev;

        if(m.count(n_prev) == 0) {
            l.push_back(n_current);
            m[n_current] = prev(l.end());
        } else {
            auto it = l.insert(m[n_prev], n_current);
            m[n_current] = it;
        }
    }

    for(const auto& x : l) {
        cout << x << '\n';
    }


    return 0;
}
