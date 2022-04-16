#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct Segtree
{
    int tree[80808];
    void update(int x, int lo, int hi, int w){
        if (lo == hi) {
            tree[x]++; return;
        }
        int mid = lo + hi >> 1;
        if (w<=mid) update(x<<1, lo, mid, w);
        else update(x<<1|1, mid+1, hi, w);
        tree[x] = tree[x<<1] + tree[x<<1|1];
    }

    int kth(int x, int lo, int hi, int k){
        if (lo == hi) return lo;
        int mid = lo + hi >> 1;
        int diff = tree[x<<1];
        if (k>diff) return kth(x<<1|1, mid+1, hi, k-diff);
        else return kth(x<<1, lo, mid, k);
    }
} tree;

int main()
{
    fastio
    int n; cin >> n;
    for (int i=1; i<=n; ++i){
        int x; cin >> x;
        tree.update(1, -10000, 10000, x);
        if (i&1) cout << tree.kth(1, -10000, 10000, i/2+1) << '\n';
        else cout << tree.kth(1, -10000, 10000, i/2) << '\n';
    }
} // namespace std;
