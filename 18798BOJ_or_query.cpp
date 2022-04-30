#include <bits/stdc++.h>

using namespace std;

int n,k,m;
int arr[252525];
int on[1010101];
int sz[1010101];


void merge(int x){
    on[x] = on[x<<1] & on[x<<1|1];
    sz[x] = sz[x<<1] + sz[x<<1|1];
}

void build(int s=1, int e=n, int x=1){
    if (s==e) {
        on[x] = arr[s-1];
        sz[x] = arr[s-1]==k;
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, x<<1); build(mid+1, e, x<<1|1);
    merge(x);
}

void update(int z, int i, int s=1, int e=n, int x=1){
    if (on[x]&z == z) return;
    if (s==e) {
        on[x]|=z;
        sz[x] = on[x]==k;
        return;
    }
    int mid = s + e >> 1;
    if (i <= mid) update(z, i, s, mid, x<<1);
    else update(z, i, mid+1, e, x<<1|1);
    merge(x);
}

int query(int l, int r, int s=1, int e=n, int x=1){
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return sz[x];
    int mid = s+e>>1;
    return query(l, r, s, mid, x<<1) + query(l, r, mid+1, e, x<<1|1);
}

int main(){
    cin >> n >> k;
    for (int i=0; i<n; ++i) cin >> arr[i];
    build();
    cin >> m;
    while (m--){
        int op, l, r, z;
        cin >> op >> l >> r;
        if (op == 1){
            cin >> z;
            for (int i=l; i<=r; ++i) update(z, i);
        } else {
            cout << query(l, r) << '\n';
        }
    }
}