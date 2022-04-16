#include <iostream>
#include <vector>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = unsigned long long;
const ll D = 1000000007;
int n,m,k;

struct SegTree
{
    vector<ll> tree;
    void init(int n, vector<ll> &arr){
        tree.resize(2*n);
        for (int i=0; i<n; ++i) tree[i+n] = arr[i];
        for (int i=n-1; i>0; --i) tree[i] = tree[i<<1] * tree[i<<1|1] % D;
    }

    void update(int x, ll z){
        x += n-1;
        tree[x] = z;
        while (x >> 1){
            tree[x>>1] = tree[x] * tree[x^1] % D;
            x>>=1;
        }
    }

    ll query(int l, int r){
        ll ret = 1;
        for (l+=n-1, r+=n; l<r; l>>=1, r>>=1){
            if (l&1) ret = ret * tree[l++] % D;
            if (r&1) ret = ret * tree[--r] % D;
        }
        return ret;
    }
} tree;


int main()
{
    fastio
    cin >> n >> m >> k;
    vector<ll> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    tree.init(n, arr);

    int T = m+k;
    while (T--){
        int x, l, r; cin >> x >> l >> r;
        if (x == 1) tree.update(l, r);
        else cout << tree.query(l,r) <<'\n';
    }
    
} // namespace std;
