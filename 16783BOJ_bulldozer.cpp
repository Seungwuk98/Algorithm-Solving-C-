#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
struct point
{
    int x, y;
    ll w;
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
    line(int i, int j, const point &p1, const point &p2)
        : i(i), j(j), dx(p2.x - p1.x), dy(p2.y - p1.y) {}

    bool operator<(const line &other) const
    {
        ll lk = dy * other.dx, rk = other.dy * dx;
        return tie(lk, i, j) < tie(rk, other.i, other.j);
    }
    bool operator==(const line &other) const
    {
        return dy * other.dx == other.dy * dx;
    }
};

struct Node
{
    ll lmx, rmx, mx, sm;
    Node() {
        lmx = rmx = mx = sm = 0;
    }

    void set(ll x) {
        lmx = rmx = mx = sm = x;
    }
};


Node tree[1<<12];
point p[1<<11];
int pos[1<<11];
int n;
const int HF = 1<<11;


Node merge(Node &l, Node &r){
    Node c;
    c.lmx = max(l.lmx, l.sm + r.lmx);
    c.rmx = max(r.rmx, r.sm + l.rmx);
    c.mx = max({l.mx, r.mx, l.rmx + r.lmx});
    c.sm = l.sm + r.sm;
    return c;
}

void build(){
    for (int i=1; i<=n; ++i) tree[HF|i].set(p[i].w);
    for (int i=HF-1; i>0; --i) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

void update(int i, ll z) {
    tree[i|=HF] = z;
    while (i>>=1) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}


void swap_seg(int i, int j) {
    swap(tree[i|=HF], tree[j|=HF]);
    while (i>>=1) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    while (j>>=1) tree[j] = merge(tree[j<<1], tree[j<<1|1]);
}


int main()
{
    fastio
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> p[i].x >> p[i].y >> p[i].w;
        pos[i] = i;
    }
    sort(p+1, p+n+1);
    build();
    vector<line> l;
    for (int i=1; i<=n-1; ++i) for (int j=i+1; j<=n; ++j) l.emplace_back(i, j, p[i], p[j]);
    sort(l.begin(), l.end());


    ll mx = tree[1].mx;
    for (int i=0, j=0; i<l.size(); i=j){
        while (j<l.size() && l[i] == l[j]) j++;
        for (int k=i; k<j; ++k) {
            int a, b;
            a = l[k].i; b = l[k].j;
            swap(pos[a], pos[b]);
            swap_seg(pos[a], pos[b]);
            mx = max(tree[1].mx, mx);
        }
    }
    cout << mx;


} // namespace std;
