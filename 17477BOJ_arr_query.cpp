#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
const int INF = 2e9 + 1000;
const int HF = 1<<19;
const int SIZE = 1<<20;
int mx[SIZE], smx[SIZE], mn[SIZE], smn[SIZE], mxcnt[SIZE], mncnt[SIZE], add[SIZE] ={0,};
ll b[SIZE] ={0,}, mnl[SIZE] = {0,}, mxl[SIZE] = {0,}, adl[SIZE] = {0,};
int n,m;

#define lx x<<1
#define rx x<<1|1


void merge(int x){
    b[x] = b[lx] + b[rx];

    if (mx[lx] == mx[rx]) {
        mx[x] = mx[lx];
        mxcnt[x] = mxcnt[lx] + mxcnt[rx];
        smx[x] = max(smx[lx], smx[rx]);
    } else if (mx[lx] > mx[rx]) {
        mx[x] = mx[lx];
        mxcnt[x] = mxcnt[lx];
        smx[x] = max(smx[lx], mx[rx]);
    } else {
        mx[x] = mx[rx];
        mxcnt[x] = mxcnt[rx];
        smx[x] = max(smx[rx], mx[lx]);
    }

    if (mn[lx] == mn[rx]){
        mn[x] = mn[lx];
        mncnt[x] = mncnt[lx] + mncnt[rx];
        smn[x] = min(smn[lx], smn[rx]);
    } else if (mn[lx] < mn[rx]){
        mn[x] = mn[lx];
        smn[x] = min(smn[lx], mn[rx]);
        mncnt[x] = mncnt[lx];
    } else {
        mn[x] = mn[rx];
        smn[x] = min(smn[rx], mn[lx]);
        mncnt[x] = mncnt[rx];
    }
}




void doMin(int x, int v, int s, int e){
    mx[x] = v; mn[x] = min(mn[x], v);
    if (mx[x] == mn[x]) smx[x] = -INF, smn[x] = INF, mxcnt[x] = mncnt[x] = (e-s+1);
    else smn[x] = min(smn[x], v);
}

void doMax(int x, int v, int s, int e){
    mn[x] = v; mx[x] = max(mx[x], v);
    if (mx[x] == mn[x]) smx[x] = -INF, smn[x] = INF, mxcnt[x] = mncnt[x] = (e-s+1);
    else smx[x] = max(smx[x], v);
}

void doAdd(int x, int v, int s, int e){
    add[x] += v;
    mx[x] += v, mn[x] += v;
    if (smn[x] != INF) smn[x] += v;
    if (smx[x] != -INF) smx[x] += v;
}

void doCnt(int p, int c, ll nl, ll xl, ll al, int s, int e){
    if (!p || mn[p] == mn[c]) {
        b[c] += mncnt[c] * nl;
        mnl[c] += nl;
    }
    if (!p || mx[p] == mx[c]) {
        b[c] += mxcnt[c] * xl;
        mxl[c] += xl;
    }
    b[c] += (e-s+1)*al;
    adl[c] += al;
}

void prop(int x, int s, int e){
    if (s == e) return;
    int mid = s + e >> 1;
    if (add[x]) doAdd(lx, add[x], s, mid), doAdd(rx, add[x], mid+1, e), add[x] = 0;
    if (mx[lx] > mx[x] && mx[x] > smx[lx]) doMin(lx, mx[x], s, mid);
    if (mx[rx] > mx[x] && mx[x] > smx[rx]) doMin(rx, mx[x], mid+1, e);
    if (mn[lx] < mn[x] && mn[x] < smn[lx]) doMax(lx, mn[x], s, mid);
    if (mn[rx] < mn[x] && mn[x] < smn[rx]) doMax(rx, mn[x], mid+1, e);
    if (mnl[x] || mxl[x] || adl[x]) {
        doCnt(x, lx, mnl[x], mxl[x], adl[x], s, mid);
        doCnt(x, rx, mnl[x], mxl[x], adl[x], mid+1, e);
        mnl[x] = mxl[x] = adl[x] = 0;
    }
}

void update_min(int v, int l, int r, int s=0, int e=HF-1, int x=1){
    if (e < l || r < s || mx[x] <= v) return;
    if (l <= s && e <= r && smx[x] < v) {
        doMin(x, v, s, e);
        doCnt(0, x, 0, 1, 0, s, e);
        return;
    }
    prop(x,s,e);
    int mid = s + e >> 1;
    update_min(v, l, r, s, mid, lx);
    update_min(v, l, r, mid+1, e, rx);
    merge(x);
}

void update_max(int v, int l, int r, int s=0, int e=HF-1, int x=1){
    if (e < l || r < s || mn[x] >= v) return;
    if (l <= s && e <= r && smn[x] > v) {
        doMax(x, v, s, e);
        doCnt(0, x, 1, 0, 0, s, e);
        return;
    }
    prop(x,s,e);
    int mid = s + e >> 1;
    update_max(v, l, r, s, mid, lx);
    update_max(v, l, r, mid+1, e, rx);
    merge(x);
}

void update_add(int v, int l, int r, int s=0, int e=HF-1, int x=1){
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        doAdd(x, v, s, e);
        doCnt(0, x, 0, 0, 1, s, e);
        return;
    }
    prop(x,s,e);
    int mid = s + e >> 1;
    update_add(v, l, r, s, mid, lx);
    update_add(v, l, r, mid+1, e, rx);
    merge(x);
}

ll query(int l, int r, int s=0, int e=HF-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0LL;
    if (l <= s && e <= r) return b[x];
    int mid = s + e >> 1;
    return query(l, r, s, mid, lx) + query(l, r, mid+1, e, rx);
}

int main()
{
    fastio
    cin >> n;
    for (int i=HF; i<SIZE; ++i) {
        smn[i] = INF; mx[i] = -INF;
        smx[i] = -INF; mn[i] = INF;
    }
    for (int i=1; i<=n; ++i) {
        int x; cin >> x;
        mn[HF|i] = mx[HF|i] = x;
        mxcnt[HF|i] = mncnt[HF|i] = 1;
    }

    for (int i=HF-1; i>0; --i) merge(i);

    cin >> m;
    int op, l, r, x;
    while (m--){
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            if (!x) continue;
            update_add(x, l, r);
        } else if (op == 2){
            cin >> x;
            update_max(x, l, r);
        } else if (op == 3){
            cin >> x;
            update_min(x, l, r);
        } else {
            cout << query(l, r) << '\n';
        }
    }
} // namespace std;
