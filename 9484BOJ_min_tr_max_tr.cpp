#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct point
{
    int x, y;
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
    int i, j, dx, dy;
    line(int i, int j, const point &p1, const point &p2)
        : i(i), j(j), dx(p2.x - p1.x), dy(p2.y - p1.y) {}

    bool operator<(const line &other) const
    {
        int ll = dy * other.dx, rl = other.dy * dx;
        return tie(ll, i, j) < tie(rl, other.i, other.j);
    }
    bool operator==(const line &other) const
    {
        return dy * other.dx == other.dy * dx;
    }
};

int ccw_abs(const point &p1, const point &p2, const point &p3)
{
    return abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

void sol(int n)
{
    vector<point> p(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; ++i){
        cin >> p[i].x >> p[i].y;
        pos[i] = i;
        // cout << p[i].x << ' ' << p[i].y << endl;
    }
    sort(p.begin()+1, p.end());
    vector<line> l;
    for (int i=1; i<=n-1; ++i) for (int j=i+1; j<=n; ++j) l.emplace_back(i, j, p[i], p[j]);
    sort(l.begin(), l.end());

    int mx = 0, mn = 1<<30;
    for (int i=0, j=0; i<l.size(); i=j){
        while (j<l.size() && l[i] == l[j]) j++;
        for (int k=i; k<j; ++k) {
            int a, b;
            a = l[k].i; b = l[k].j;
            swap(pos[a], pos[b]);
            swap(p[pos[a]], p[pos[b]]);
            if (pos[a] > pos[b]) swap(a,b);
            if (pos[a] > 1) {
                mn = min(mn, ccw_abs(p[pos[a]], p[pos[b]], p[pos[a]-1]));
                mx = max(mx, ccw_abs(p[pos[a]], p[pos[b]], p[1]));
            }
            if (pos[b] < n) {
                mn = min(mn, ccw_abs(p[pos[a]], p[pos[b]], p[pos[b]+1]));
                mx = max(mx, ccw_abs(p[pos[a]], p[pos[b]], p[n]));
            }
        }
    }
    cout << mn/2 << '.' << mn*5%10 << ' ' << mx/2 << '.' << mx*5%10 << '\n';
}

int main()
{
    fastio
    int n;
    while (cin >> n)
    {
        if (n == 0)
            break;
        sol(n);
    }
}