#include <bits/stdc++.h>
#define INF 1000000000
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int tree[1<<24];
int sz = 1<<23;
int query(int l, int r){
    int ret = INF;
    for (l|=sz, r|=sz; l<=r; l>>=1, r>>=1){
        if (l&1) ret = min(ret, tree[l++]);
        if (~r&1) ret = min(ret, tree[r--]);
    }
    return ret;
}


int main()
{
    fastio
    int n, l; cin >> n >> l;
    for (int i=0; i<n; ++i) cin >> tree[i|sz];
    for (int i=sz-1; i; --i) tree[i] = min(tree[i<<1], tree[i<<1|1]);
    for (int i=0; i<n; ++i) cout << query(max(0,i-l+1),i) << ' ';

} // namespace std;
