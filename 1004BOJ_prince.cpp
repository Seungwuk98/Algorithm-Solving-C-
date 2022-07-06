#include <bits/stdc++.h>

using namespace std;

bool in(int x1, int y1, int x, int y, int r) {
    int D = (x-x1)*(x-x1) + (y-y1)*(y-y1);
    return D < r*r;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int n; cin >> n;
        int c1 = 0, c2 = 0;
        while (n--) {
            int x, y, r; cin >> x >> y >> r;
            bool b1, b2;
            b1 = in(x1, y1, x, y, r);
            b2 = in(x2, y2, x, y, r);
            if (b1 && !b2) c1++;
            else if (!b1 && b2) c2++;
        }
        cout << c1 + c2 << '\n';
    }
} // namespace std;
