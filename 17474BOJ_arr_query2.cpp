#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

int mx[1<<21] = {0,};
int smx[1<<21];
ll sm[1<<21];
int cnt[1<<21] ={0,};
int lazy[1<<21];
int n, m;
const int HF = 1<<20;
const int INF = 2147483647;

void merge(int x){
    sm[x] = sm[x<<1] + sm[x<<1|1];
    int lmx = mx[x<<1], rmx = mx[x<<1|1], lsmx = smx[x<<1], rsmx = smx[x<<1|1];
    if (lmx == rmx) {
        mx[x] = lmx;
        cnt[x] = cnt[x<<1] + cnt[x<<1|1];
        smx[x] = max(lsmx, rsmx);
    } else if (lmx > rmx) {
        mx[x] = lmx;
        cnt[x] = cnt[x<<1];
        smx[x] = max(lsmx, rmx);
    } else {
        mx[x] = rmx;
        cnt[x] = cnt[x<<1|1];
        smx[x] = max(rsmx, lmx);
    }
}

void prop(int x, int s, int e){
    if (lazy[x] >= mx[x]) return;
    sm[x] -= (ll)(mx[x] - lazy[x]) * cnt[x];
    mx[x] = lazy[x];
    if (s^e){
        lazy[x<<1] = min(lazy[x<<1], lazy[x]);
        lazy[x<<1|1] = min(lazy[x<<1|1], lazy[x]);
    }
    lazy[x] = INF;
}

void update(int z, int l, int r, int s=0, int e=HF-1, int x=1) {
    prop(x,s,e);
    if (e < l || r < s || mx[x] <= z) return;
    if (l <= s && e <= r && smx[x] < z) {
        lazy[x] = z; prop(x,s,e);
        return;
    }
    int mid = s + e >> 1;
    update(z, l, r, s, mid, x<<1); update(z, l, r, mid+1, e, x<<1|1);
    merge(x);
}

int query_mx(int l, int r, int s=0, int e=HF-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return mx[x];
    int mid = s + e >> 1;
    return max(query_mx(l, r, s, mid, x<<1), query_mx(l, r, mid+1, e, x<<1|1));
}

ll query_sm(int l, int r, int s=0, int e=HF-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return sm[x];
    int mid = s + e >> 1;
    return query_sm(l, r, s, mid, x<<1) + query_sm(l, r, mid+1, e, x<<1|1);
}


int main()
{
    fastio
    cin >> n;
    fill(&lazy[0], &lazy[1<<21], INF);
    fill(&smx[0], &smx[1<<21], -1);
    for (int i=1; i<=n; ++i) {
        cin >> mx[i|HF], cnt[i|HF]=1;
        sm[i|HF] = mx[i|HF];
    } 
    for (int i=HF-1; i>0; --i) merge(i);
    cin >> m;
    int op, l, r, z;
    while (m--){
        cin >> op >> l >> r;
        if (op == 1){
            cin >> z;
            update(z, l, r); 
        } else if (op == 2){
            cout << query_mx(l, r) << '\n';
        } else {
            cout << query_sm(l, r) << '\n';
        }
    }

} // namespace std;


