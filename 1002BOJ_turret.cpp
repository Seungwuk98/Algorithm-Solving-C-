#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int T; cin >> T;
    while (T--) {
        ll x1,y1,r1,x2,y2,r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        ll sqdist = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
        ll d1 = (r1+r2)*(r1+r2), d2 = (r1-r2)*(r1-r2);
        if (sqdist) {
            cout << ((d2 < sqdist && sqdist < d1) ? 2 : (d1 == sqdist || d2 == sqdist) ? 1 : 0) << '\n';
        } else {
            cout << (r1 == r2 ? -1 : 0)  << '\n';
        }
    }
}