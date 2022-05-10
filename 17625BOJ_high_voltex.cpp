#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
struct point
{
    ll x, y;
    point() {}

    bool operator<(const point &other) const
    {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }

    bool operator==(const point &other) const
    {
        return (x == other.x && y == other.y);
    }
};

struct line
{
    int i, j;
    ll dx, dy;
    int rot;
    line(int i, int j, const point &p1, const point &p2, int rot)
        : i(i), j(j), dx(p2.x - p1.x), dy(p2.y - p1.y) {
            if (rot == -1) {
                if (dy < 0) dy = -dy;
                else dx = -dx;
                swap(dx, dy);
            }
            this->rot = rot;
        }

    bool operator<(const line &other) const
    {
        ll lk = dy * other.dx, rk = other.dy * dx;
        return tie(lk, rot, i, j) < tie(rk, other.rot, other.i, other.j);
    }
    bool operator==(const line &other) const
    {
        return dy * other.dx == other.dy * dx;
    }
};

point p[2020];
int pos[2020];
int n;

double line_to_point(const line &L, const point &P) {
    point &p1 = p[pos[L.i]];
    ll dx = L.dx, dy = L.dy;
    double d = sqrt(dx*dx + dy*dy);
    double b = dy*P.x/d - dx*P.y/d - p1.x*dy/d + p1.y*dx/d;
    return abs(b);
}

double point_to_point(const point &p1, const point &p2){
    return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y));
}

int main()
{
    fastio
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> p[i].x >> p[i].y;
        pos[i] = i;
    }
    sort(p+1, p+n+1);
    vector<line> l;
    for (int i=1; i<=n-1; ++i) for (int j=i+1; j<=n; ++j) 
        l.emplace_back(i, j, p[i], p[j], 1), l.emplace_back(i, j, p[i], p[j], -1);
    sort(l.begin(), l.end());


    double mx = 0;
    for (int i=0, j=0; i<l.size(); i=j){
        while (j<l.size() && l[i] == l[j]) j++;
        for (int k=i; k<j; ++k) {
            int a, b;
            a = l[k].i; b = l[k].j;
            if (l[k].rot == 1){
                swap(pos[a], pos[b]);
                swap(p[pos[a]], p[pos[b]]);
                if (pos[a] > pos[b]) swap(a,b);
                if (pos[a] > 1) {
                    mx = max(mx, line_to_point(l[k], p[pos[a]-1]));
                } 
                if (pos[b] < n) {
                    mx = max(mx, line_to_point(l[k], p[pos[b]+1]));
                } 
            } else {
                if (abs(pos[a] - pos[b]) == 1) mx = max(mx, point_to_point(p[pos[a]], p[pos[b]]));
            }
        }
    }
    cout << fixed << setprecision(10) << mx/2;


} // namespace std;
