#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;
using ll = long long;
int n,q;

struct Segtree
{
    vector<ll> tree;
    Segtree() {}
    Segtree(vector<ll> &arr){
        tree.resize(2*n);
        for (int i=0; i<n; ++i) tree[i+n] = arr[i];
        for (int i=n-1; i>0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
    }
    void update(int i, ll z){
        i+=n;
        tree[i] = z;
        while (i>>1){
            tree[i>>1] = tree[i] + tree[i^1];
            i>>=1;
        }
    }
    ll query(int l, int r){
        ll ret = 0;
        for (l+=n, r+=n+1; l<r; l>>=1, r>>=1){
            if (l&1) ret += tree[l++];
            if (r&1) ret += tree[--r];
        }
        return ret;
    }
};

struct Segtree2D
{
    vector<Segtree> tree;
    void init(vector<vector<ll>> &arr){
        tree.resize(2*n);
        for (int i=0; i<n; ++i) tree[i+n] = Segtree(arr[i]);
        for (int i=n-1; i>0; --i) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    }
    Segtree merge(Segtree &a, Segtree &b){
        Segtree ret = Segtree();
        ret.tree.resize(2*n);
        for (int i=0; i<2*n; ++i) ret.tree[i] = a.tree[i] + b.tree[i];
        return ret;
    }
    void merge(Segtree &ret, Segtree &a, Segtree &b, int y){
        y+=n;
        while (y){
            ret.tree[y] = a.tree[y] + b.tree[y];
            y>>=1;
        }
    }
    void update(int x, int y, ll z){
        x += n;
        tree[x].update(y,z);
        while (x>>1){
            merge(tree[x>>1], tree[x], tree[x^1], y);
            x>>=1;
        }
    }
    ll query(int u, int d, int l, int r){
        ll ret = 0;
        for (u+=n, d+=n+1; u<d; u>>=1, d>>=1){
            if (u&1) ret += tree[u++].query(l,r);
            if (d&1) ret += tree[--d].query(l,r);
        }
        return ret;
    }
} tree;

int main()
{
    fastio
    cin >> n >> q;
    vector<vector<ll>> arr(n);
    for (int i=0; i<n; ++i){
        arr[i].resize(n);
        for (int j=0; j<n; ++j) cin >>  arr[i][j];
    }
    tree.init(arr);

    while (q--){
        int k,x,y,z,w;
        cin >> k;
        if (k){
            cin >> x >> y >> z >> w;
            cout << tree.query(--x,--z,--y,--w) << '\n';
        }else{
            cin >> x >> y >> w;
            tree.update(--x,--y,w);
        }
    }


} // namespace std;
