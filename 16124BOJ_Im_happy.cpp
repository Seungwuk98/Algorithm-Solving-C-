#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

#define range(l) for (int i=0; i<10; ++i) (l[i]) = i;
#define cpy(x, y) for (int i=0; i<10; ++i) x[i] = y[i];

ll K[1<<20];
const int HF = 1<<20;
const ll P = 998'244'353;
int n,q;
string s;

struct Node {
    ll val[10] = {0,};
    int lazy[10];
    int len;
    Node() {
        len = 0;
        range(lazy);
    }
    void set(int x) {
        len = 1;
        val[x] = 1;
    }
} tree[1<<21];

void merge(ll *ret, ll *left, ll *right, int rs) {
    for (int i=0; i<10; ++i) ret[i] = (left[i] * K[rs] % P + right[i]) % P;
}

void build() {
    for (int i=1; i<=n; ++i) tree[i|HF].set(s[i-1] - '0');
    for (int i=HF-1; i>0; --i) {
        merge(tree[i].val, tree[i<<1].val, tree[i<<1|1].val, tree[i<<1|1].len);
        tree[i].len = tree[i<<1].len + tree[i<<1|1].len;
    } 
}

void prop(int x, int s, int e) {
    bool c = 1;
    for (int i=0; i<10; ++i) if (tree[x].lazy[i] != i) {
        c = 0; break;
    }
    if (c) return ;
    ll tmp[10] = {0,};
    for (int i=0; i<10; ++i) tmp[tree[x].lazy[i]] = (tmp[tree[x].lazy[i]] + tree[x].val[i]) % P;
    cpy(tree[x].val, tmp);
    if (s ^ e) {
        for (int cx : {x<<1, x<<1|1}) {
            for (int i=0; i<10; ++i) tmp[i] = tree[x].lazy[tree[cx].lazy[i]];
            cpy(tree[cx].lazy, tmp);
        }
    }
    range(tree[x].lazy);
}

void update(int f, int t, int l, int r, int s=0, int e=HF-1, int x=1) {
    prop(x,s,e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        tree[x].lazy[f] = t;
        prop(x,s,e);
        return;
    }
    int mid = s + e >> 1;
    update(f, t, l, r, s, mid, x<<1);
    update(f, t, l, r, mid+1, e, x<<1|1);
    merge(tree[x].val, tree[x<<1].val, tree[x<<1|1].val, tree[x<<1|1].len);
}

ll convert(ll *val) {
    ll ret = 0;
    for (int i=0; i<10; ++i) ret = (ret + val[i] * i % P) % P;
    return ret;
}

pair<ll, int> query(int l, int r, int s=0, int e=HF-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return {0, 0};
    if (l <= s && e <= r) return {convert(tree[x].val), tree[x].len};
    ll lval, rval;
    int mid = s + e >> 1, llen, rlen;
    tie(lval, llen) = query(l, r, s, mid, x<<1);
    tie(rval, rlen) = query(l, r, mid+1, e, x<<1|1);
    return {(lval * K[rlen] % P + rval) % P, llen + rlen};
}

int main()
{
    fastio
    cin >> s;
    n = s.size();
    K[0] = 1;
    for (int i=1; i<HF; ++i) K[i] = K[i-1]*10%P;
    build();
    cin >> q;
    int op, l, r, f, t;
    while (q--){
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> f >> t;
            update(f, t, l, r);
        } else {
            ll val; int len;
            tie(val, len) = query(l, r);
            cout << val << '\n';
        }
    }

} // namespace std;
