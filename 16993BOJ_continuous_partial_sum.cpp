#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF 1000000000
using namespace std;
using ll = long long;
struct Node{
    ll lmax, rmax, mx, sm;
    Node(){
        lmax = rmax = mx = sm = -INF;
    }
    void set(int x){
        lmax = rmax = mx = sm = x;
    }
};

Node tree[1<<18];
int HALF = 1<<17;
int n;

Node merge(Node left, Node right){
    Node ret;
    ret.lmax = max(left.lmax, left.sm + right.lmax);
    ret.rmax = max(right.rmax, right.sm + left.rmax);
    ret.mx = max({left.mx, right.mx, left.rmax + right.lmax});
    ret.sm = left.sm + right.sm;
    return ret;
}

void build(vector<int> &arr){
    for (int i=0; i<n; ++i) tree[i|HALF].set(arr[i]);
    for (int i=HALF-1; i; --i) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

Node query(int l, int r){
    Node retl, retr;
    for (l+=HALF, r+=HALF; l<=r; l>>=1, r>>=1){
        if (l&1) retl = merge(retl, tree[l++]);
        if (~r&1) retr = merge(tree[r--], retr);
    }
    return merge(retl, retr);
}


int main()
{
    fastio
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    build(arr);
    int m; cin >> m;
    while (m--){
        int i,j; cin >> i >> j;
        Node ret = query(--i, --j);
        cout << ret.mx << '\n';
    }
}