#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

struct Node
{
    ll lmx, rmx, mx, sm, val;
    Node() {
        lmx = rmx = mx = sm = val = -110010101;
    }
    void set(){
        lmx = rmx = mx = sm = val? -101020203 : 1;
    }
};


ll arr[101010];
Node tree[404040];
int n, m;

Node merge(Node l, Node r){
    Node ret;
    ret.lmx = max(l.lmx, l.sm + r.lmx);
    ret.rmx = max(r.rmx, r.sm + l.rmx);
    ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
    ret.sm = l.sm + r.sm;
    return ret;
}

void build(int s=2, int e=n-1, int x=1){
    if (s == e) {
        tree[x].val = arr[s]*2 - arr[s-1] - arr[s+1];
        tree[x].set();
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, x<<1); build(mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void update(int i, ll z, int s=2,  int e=n-1, int x=1){
    if (s == e) {
        tree[x].val += z;
        tree[x].set();
        return;
    }
    int mid = s + e >> 1;
    if (i<=mid) update(i, z, s, mid, x<<1);
    else update(i, z, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

Node query(int l, int r, int s=2, int e=n-1, int x=1){
    if (s < l || r < e) return Node();
    if (l <= s && e <= r) return tree[x];
    int mid = s + e >> 1;
    return merge(query(l, r, s, mid, x<<1), query(l, r, mid+1, e, x<<1|1));
}

int main()
{
    fastio
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> arr[i];
    build();
    cin >> m;
    int op, i, j; ll x, y;
    while (m--) {
        cin >> op >> i >> j;
        if (op == 1) {
            cin >> x >> y;
            if (i > 2) update(i-1, -x);
            if (i > 1) update(i, x-y);
            if (j < n) update(j, x+(j-i+1)*y);
            if (j < n-1) update(j+1, -x-(j-i)*y);
        } else {
            if (i == j) cout << 1 << '\n';
            else if (i+1 == j) cout << 2 << '\n';
            else {
                Node ret = query(i+1, j-1);
                if (ret.mx < 0) cout << 2 << '\n';
                else cout << ret.mx + 2 << '\n';
            }
        }
    }
} // namespace std;
