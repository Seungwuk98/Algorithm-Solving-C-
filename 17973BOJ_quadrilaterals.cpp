#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

struct P
{
    ll x, y;
    P() {}
    P(ll x, ll y) : x(x), y(y) {}
    bool operator<(const P &other) const {
        return tie(x,y) < tie(other.x, other.y);
    }
    friend istream& operator>>(istream &in, P &p) {
        in >> p.x >> p.y;
        return in;
    }
} point[1010];

int pos[1010];

struct line
{
    int i, j;
    ll dx, dy;

    line(int i, int j) 
        : i(i), j(j), dx(point[j].x-point[i].x), dy(point[j].y - point[i].y) {}

    bool operator<(const line &l) const {
        ll le = dy * l.dx, re = l.dy * dx;
        return tie(le, i, j) < tie(re, i, j);
    }
};

ll ccw(P &p1, P &p2, P &p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

ll area(P &p1, P &p2, P &p3){
    return abs(ccw(p1,p2,p3));
}

int main()
{
    fastio
    int n; cin >> n;
    for (int i=1; i<=n; ++i) {
        cin >> point[i];
        pos[i] = i;
    }
    sort(point+1, point+n+1);
    vector<line> L;
    for (int i=1; i<=n-1; i++) for (int j=i+1; j<=n; ++j) L.emplace_back(i, j);
    sort(L.begin(), L.end());
    ll ret = 0, mn = 8e18, sm = 0;

    for (int i=0; i<L.size(); ++i) {
        int a, b;
        tie(a,b) = tie(L[i].i, L[i].j);
        swap(pos[a], pos[b]);
        swap(point[pos[a]], point[pos[b]]);
        if (pos[a] > pos[b]) swap(a,b);
        ret += (ll)(pos[a]-1) * (n - pos[b]);
        for (int x : {1, 2}) for (int y : {1, 2}) {
            if (pos[a]-x >= 1 && pos[b]+y <= n) {
                ll ar = area(point[pos[a]], point[pos[b]], point[pos[a]-x]) + area(point[pos[a]], point[pos[b]], point[pos[b]+y]);
                if (mn > ar) {
                    mn = ar;
                    sm = 0;
                }
                if (mn == ar) {
                    sm ++;
                    if ((ccw(point[pos[a]-x], point[pos[b]+y], point[pos[a]])>0) == (ccw(point[pos[a]-x], point[pos[b]+y], point[pos[b]])>0)) sm++;
                }
            }
        }
    }
    cout << ret + sm;
} // namespace std;
