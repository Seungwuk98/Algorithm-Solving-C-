#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

ll arr[1<<18];
ll lazyx[1<<18];
ll lazyy[1<<18];
const int HF = 1<<17;
int n, m;

void smbuild(){
    for (int i=1; i<=n; ++i) cin >> arr[i|HF];
}

void prop(int x, int s, int e){
    if (!lazyx[x] && !lazyy[x]) return;
    arr[x] += lazyx[x];
    if (s ^ e){
        int mid = s + e >> 1;   
        lazyx[x<<1] += lazyx[x];
        lazyy[x<<1] += lazyy[x];
        lazyx[x<<1|1] += lazyx[x] + lazyy[x] * (mid+1-s);
        lazyy[x<<1|1] += lazyy[x];
    }
    lazyx[x] = lazyy[x] = 0;
}

void update(ll x, ll y, ll z, int l, int r, int s=0, int e=HF-1, int d=1){
    prop(d, s, e);
    // cout << x << ' ' << y << ' ' << z << ' ' << s << ' ' << e << endl;
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        lazyx[d] = y;
        lazyy[d] = z;
        prop(d,s,e);
        return ;
    }
    int mid = s + e >> 1;
    update(x, y, z, l, r, s, mid, d<<1);
    update(x, x + z * (mid+1-l), z, l, r, mid+1, e, d<<1|1);
}

ll get(int i, int s=0, int e=HF-1, int x=1){
    prop(x, s, e);
    if (s == e) return arr[x];
    int mid = s + e >> 1;
    if (i <= mid) return get(i, s, mid, x<<1);
    return get(i, mid+1, e, x<<1|1);
}


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

Node tree[1<<18];

Node merge(Node l, Node r){
    Node ret;
    ret.lmx = max(l.lmx, l.sm + r.lmx);
    ret.rmx = max(r.rmx, r.sm + l.rmx);
    ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
    ret.sm = l.sm + r.sm;
    return ret;
}

void treebuild(){
    for (int i=2; i<=n-1; ++i) {
        int j = i|HF;
        tree[j].val = arr[j]*2 - arr[j-1] - arr[j+1];
        tree[j].set();
    } 
    for (int i=HF-1; i>0; --i) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

void tree_update(int i, ll z) {
    tree[i|HF].val = z;
    tree[i|=HF].set();
    while (i>>=1) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

Node query(int l, int r, int s=0, int e=HF-1, int x=1){
    if (e < l || r < s) return Node();
    if (l <= s && e <= r) return tree[x];
    int mid = s + e >> 1;
    return merge(query(l, r, s, mid, x<<1), query(l, r, mid+1, e, x<<1|1));
}


int main()
{
    fastio
    cin >> n;
    smbuild();
    treebuild();
    cin >> m;
    int op, i, j; ll x, y;
    while (m--) {
        cin >> op >> i >> j;
        if (op == 1){
            cin >> x >> y;
            update(x, x, y, i, j);
            for (int t : {i, i-1, j, j+1}) {
                if (1 < t && t < n) tree_update(t, get(t)*2 - get(t-1) -get(t+1));
            }
        } else {
            if (i == j) cout << 1 << '\n';
            else if (i+1 == j) cout << 2 << '\n';
            else {
                Node ret = query(i+1, j-1);
                if (ret.mx < 0) cout << 2 << '\n';
                else cout << ret.mx + 2 << '\n';
            }
        }
        // for (int i=1; i<=n; ++i) cout << get(i) << ' ';
        // cout << endl;
    }
} // namespace std;
