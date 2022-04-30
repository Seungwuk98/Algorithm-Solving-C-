#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int n,k,m;
int on[1<<19];
int sz[1<<19];
const int hf = 1<<18;


void merge(int x){
    on[x] = on[x<<1] & on[x<<1|1];
    sz[x] = sz[x<<1] + sz[x<<1|1];
}


void update(int z, int l, int r, int s=0, int e=hf-1, int x=1){
    if (e < l || r < s || (on[x]&z) == z) return;
    if (l <= s && e <= r) {
        on[x] |= z;
    }
    if (s==e) {
        sz[x] = on[x]==k;
        return;
    } 

    int mid = s + e >> 1;
    update(z, l, r, s, mid, x<<1);
    update(z, l, r, mid+1, e, x<<1|1);
    merge(x);
}

int query(int l, int r){
    int ret = 0;
    for (l|=hf, r|=hf; l<=r; l>>=1, r>>=1){
        if (l&1) ret += sz[l++];
        if (~r&1) ret += sz[r--];
    }
    return ret;
}

int main(){
    cin >> n >> k;
    for (int i=1; i<=n; ++i) {
        cin >> on[i|hf];
        sz[i|hf] = on[i|hf]==k; 
    }
    for (int i=hf-1; i>0; --i) merge(i);

    cin >> m;
    int op, l, r, z;
    while (m--){
        cin >> op >> l >> r;
        if (op == 1){
            cin >> z;
            update(z, l, r);
        } else {
            cout << query(l, r) << '\n';
        }
    }
}