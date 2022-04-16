#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
vector<int> arr;
int n,k;

struct Segtree
{
    int tree[300000] = {0,};
    void update(int w, int c=1, int s=0, int e=65536, int x=1){
        if (s==e){
            tree[x]+=c; return;
        }
        int mid = s+e>>1;
        if (w <= mid) update(w, c, s, mid, x<<1);
        else update(w, c, mid+1, e, x<<1|1);
        tree[x] = tree[x<<1] + tree[x<<1|1];
    }

    int query(int k, int s=0, int e=65536, int x=1){
        if (s==e) return s;
        int mid = s+e>>1;
        int diff = tree[x<<1];
        if (k > diff) return query(k-diff, mid+1, e, x<<1|1);
        else return query(k, s, mid, x<<1);
    }
} tree;



int main()
{
    fastio
    cin >> n >> k;
    long long sum=0;
    for (int i=0; i<n; ++i){
        int x; cin >> x;
        arr.push_back(x);
        tree.update(x);
        if (i>=k) tree.update(arr[i-k],-1);
        sum += tree.query(i<k-1? 0:k&1? k/2+1:k/2 );
    }
    cout << sum;
} // namespace std;
