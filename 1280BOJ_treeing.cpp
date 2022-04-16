#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

ll tree[1<<19] = {0,}, num[1<<19] = {0,};
const int sz = 1<<18;
const ll MOD = 1000000007;

void update(int w){
    tree[w|sz] += w;
    tree[w|sz] %= MOD;
    num[w|sz] ++;
    w|=sz;
    while (w>>=1) {
        tree[w] = tree[w<<1] + tree[w<<1|1]; tree[w] %= MOD;
        num[w] = num[w<<1] + num[w<<1|1];
    }
}

pair<ll, int> query(int l, int r){
    ll ret1 = 0;
    int ret2 = 0;
    for (l|=sz, r|=sz; l<=r; l>>=1, r>>=1){
        if (l&1) {
            ret1 += tree[l]; ret1 %= MOD;
            ret2 += num[l++];
        }
        if (~r&1) {
            ret1 += tree[r]; ret1 %= MOD;
            ret2 += num[r--];
        }
    }
    return {ret1, ret2};
}


int main()
{
    fastio
    int n; cin >> n;
    ll ret = 1;
    for (int i=0; i<n; ++i){
        int x; cin >> x;
        update(x);
        if (i){
            ll left, right; ll ln, rn;
            tie(left, ln) = query(0, x-1);
            tie(right, rn) = query(x+1, 200000);
            ret *= (ln * x - left + right - rn * x)%MOD;
            ret %= MOD;
        }
    }
    if (ret < 0) ret += MOD;
    cout << ret;
} // namespace std;
