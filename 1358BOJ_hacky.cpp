#include <bits/stdc++.h>

using namespace std;

bool in(int x1, int y1, int x, int y, int r) {
    int D = (x-x1)*(x-x1) + (y-y1)*(y-y1);
    return D <= r*r;
}

int main()
{
    int w, h, x, y, p; cin >> w >> h >> x >> y >> p;
    int r = h>>1;
    int x1 = x, y1 = y+r;
    int x2 = x+w, y2 = y+r;
    int ans = 0;

    while (p--) {
        int xx, yy; cin >> xx >> yy;
        if (in(xx, yy, x1, y1, r) || in(xx, yy, x2, y2, r) || (x1 <= xx && xx <= x2 && y <= yy && yy <= y+h)) ans++;
    }
    cout << ans;
} // namespace std;
