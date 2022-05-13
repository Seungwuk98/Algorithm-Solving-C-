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
        sm = x;
        lmx = rmx = mx = max(x,0LL);
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
    if (tree[i|HF].mx == z) return;
    tree[i|=HF].set(z);
    while (i>>=1) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}


void give_swap(int i, int j) {
    if (tree[i|HF].mx) {
        tree[j|HF].set(tree[j|HF].sm + tree[i|HF].sm);
        tree[i|HF].set(0);
        while (i>>=1) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
        while (j>>=1) tree[j] = merge(tree[j<<1], tree[j<<1|1]);
    }
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
        int a, b;
        for (int k=i; k<j; ++k) {
            a = l[k].i; b = l[k].j;
            give_swap(pos[a], pos[b]);
            swap(pos[a], pos[b]);
            swap(p[pos[a]], p[pos[b]]);
        }
        mx = max(mx, tree[1].mx);
        for (int k=i; k<j; ++k) {
            a = l[k].i; b = l[k].j;
            update(pos[a], p[pos[a]].w);
            update(pos[b], p[pos[b]].w);
        }
    }
    cout << mx;


} // namespace std;
