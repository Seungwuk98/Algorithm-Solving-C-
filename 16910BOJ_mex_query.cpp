#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()


using namespace std;
using ll = long long;
const ll INF = 1'000'000'000'000'000'000LL +1;
int sz;

int cnt[1616161] = {0,};
int lazy[1616161] = {0,};

void prop(int x, int s, int e) {
    if (lazy[x] == 0) return;
    int mid = s + e >> 1;
    if (lazy[x] == 1){
        cnt[x] = 0;
        if (s ^ e) {
            lazy[x<<1] = lazy[x<<1|1] = 1;
        }
    } else if (lazy[x] == 2) {
        cnt[x] = e - s + 1;
        if (s ^ e) {
            lazy[x<<1] = lazy[x<<1|1] = 2;
        }
    } else {
        cnt[x] = (e-s+1) - cnt[x];
        if (s ^ e) {
            lazy[x<<1] ^= 3;
            lazy[x<<1|1] ^= 3;
        }
    }
    lazy[x] = 0;
}

void merge(int x){
    cnt[x] = cnt[x<<1] + cnt[x<<1|1];
}

void build(int s=0, int e=sz-1, int x=1){
    if (s == e) {
        cnt[x] = 1;
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, x<<1);
    build(mid+1, e, x<<1|1);
    merge(x);
}

void update(int op, int l, int r, int s=0, int e=sz-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        lazy[x] = op;
        prop(x,s,e);
        return;
    }
    int mid = s + e >> 1;
    update(op, l, r, s, mid, x<<1);
    update(op, l, r, mid+1, e, x<<1|1);
    merge(x);
}

int query(int k=1, int s=0, int e=sz-1, int x=1){
    prop(x,s,e);
    if (s == e) return s;
    int mid = s + e >> 1;
    prop(x<<1, s, mid);
    int diff = cnt[x<<1];
    if (k <= diff) return query(k, s, mid, x<<1);
    return query(k-diff, mid+1, e, x<<1|1);
}

struct qry
{
    int op; ll l, r;
} Q[101010];


int main()
{
    fastio
    int n; cin >> n;
    int op; ll l, r;
    vector<ll> x;
    x.push_back(1);
    x.push_back(INF);
    for (int i=0; i<n; ++i) {
        cin >> Q[i].op >> Q[i].l >> Q[i].r;
        x.push_back(Q[i].l);
        x.push_back(Q[i].r);
        x.push_back(Q[i].l+1);
        x.push_back(Q[i].r+1);
    }
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    sz = x.size();
    build();
    for (int i=0; i<n; ++i) {
        Q[i].l = lower_bound(all(x), Q[i].l) - x.begin();
        Q[i].r = lower_bound(all(x), Q[i].r) - x.begin();
        update(Q[i].op, Q[i].l, Q[i].r);
        int ret = query();
        cout << x[ret] << '\n';
    }

    
} // namespace std;
