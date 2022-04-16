#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int tree[1<<20];
int lazy[1<<20];
int n;
void build(int s=1, int e=n, int x=1){
    if (s==e){
        cin >> tree[x];
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, x<<1); build(mid+1, e, x<<1|1);
    tree[x] = tree[x<<1]^tree[x<<1|1];
}
void prop(int x, int s, int e){
    if (!lazy[x]) return;
    if (~(e-s)&1) tree[x]^=lazy[x];
    if (s^e) {
        lazy[x<<1] ^= lazy[x];
        lazy[x<<1|1] ^= lazy[x];
    }
    lazy[x] = 0;
}

void update(int z, int l, int r, int s=1, int e=n, int x=1){
    prop(x, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        lazy[x] ^= z; prop(x, s, e);
        return;
    }
    int mid = s + e >> 1;
    update(z, l, r, s, mid, x<<1); update(z, l, r, mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] ^ tree[x<<1|1];
}

int query(int i, int s=1, int e=n, int x=1){
    prop(x, s, e);
    if (s == e) return tree[x];
    int mid = s + e >> 1;
    if (i<=mid){
        return query(i, s, mid, x<<1);
    } else {
        return query(i, mid+1, e, x<<1|1);
    }
}

int main(){
    fastio
    cin >> n;
    build();
    int m; cin >> m;
    while (m--){
        int op, l, r, x;
        cin >> op;
        if (op == 1){
            cin >> l >> r >> x;
            update(x, ++l, ++r);
        } else {
            cin >> l;
            cout << query(++l) <<'\n';
        }
    }
}