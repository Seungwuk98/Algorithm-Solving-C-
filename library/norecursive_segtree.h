#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N;
ll tree[1<<19];
int HALF = 1<<18;

void build(vector<ll> &arr){
    for (int i=0; i<N; ++i) tree[i+HALF] = arr[i];
    for (int i=HALF-1; i>0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
}

void update(int idx, ll plus){
    idx += HALF;
    tree[idx] += plus;
    while (idx >>= 1) tree[idx] = tree[idx<<1] + tree[idx<<1|1];
}

ll query(int L, int R){
    ll ret = 0;
    for (L += HALF, R += HALF; L <= R; L>>=1, R>>=1){
        if (L&1) ret += tree[L--];
        if (~R&1) ret += tree[R--];
    }
    return ret;
}

