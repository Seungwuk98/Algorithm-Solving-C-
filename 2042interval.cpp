#include <bits/stdc++.h>

using ll = long long;
using namespace std;

int main(){
    int n,m,k,x; cin >> n >> m >> k;
    ll arr[n], pre[n+1], tree[n+1];
    for (int i=1; i<=n; ++i){
        cin >> arr[i-1];
        pre[i] = pre[i-1] + arr[i-1];
        tree[i] = pre[i] - pre[i&~(i&-i)];
    }
    int T = m+k;
    int op; ll l,r;
    while (T--){
        cin >> op >> l >> r;
        if (op == 1){
            ll t = arr[l-1];
            arr[l-1] = r;
            t = r-t;
            for (; l<=n; l+=l&-l) tree[l] += t;
        } else {
            ll ret = 0;
            for (; r; r-=r&-r) ret += tree[r];
            for (l--; l; l-=l&-l ) ret -= tree[l];
            cout << ret << '\n';
        }
    }

}