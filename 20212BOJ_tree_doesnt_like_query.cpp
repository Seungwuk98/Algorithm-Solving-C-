#include <bits/stdc++.h>
#include <algorithm>
#define INF 1000000001
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long;
struct Node
{
    ll sum, lazy;
    Node *l, *r;
    Node(){
        sum = lazy = 0;
        l = r = nullptr;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};

struct Segtree
{
    Node *tree;
    Segtree(){
        tree = new Node();
    }
    ~Segtree(){
        if (tree) delete tree;
    }
    void prop(Node *x, int s, int e){
        if (!x->lazy) return;
        x->sum += (e-s+1) * x->lazy;
        if (s == e) {
            x->lazy = 0;
            return;
        }
        if (!x->l) x->l = new Node();
        if (!x->r) x->r = new Node();
        x->l->lazy += x->lazy;
        x->r->lazy += x->lazy;
        x->lazy = 0;
    }

    void update(Node *x, int k, int l, int r, int s = 1, int e = INF){
        prop(x, s, e);
        if (e < l || r < s) return;
        if (l <= s && e <= r) {
            x->lazy += k; prop(x, s, e); 
            return;
        }
        if (!x->l) x->l = new Node();
        if (!x->r) x->r = new Node();
        int mid = s + e >> 1;
        update(x->l, k, l, r, s, mid); update(x->r, k, l, r, mid+1, e);
        x->sum = x->l->sum + x->r->sum;
    }

    ll query(Node *x, int l, int r, int s = 1, int e = INF){
        prop(x, s, e);
        if (e < l || r < s) return 0;
        if (l <= s && e <= r) {
            return x->sum;
        } 
        int mid = s + e >> 1;
        return (x->l? query(x->l, l, r, s, mid) : 0) + (x->r? query(x->r, l, r, mid+1, e) : 0);
    }

} tree;


using t3 = tuple<int, int, int>;
using t4 = tuple<int, int, int, int>;


int main()
{
    int n; cin >> n;
    vector<t3> qry1;
    vector<t4> qry2;
    for (int x=0, y=0; x<n; ++x) {
        int q,i,j,k; cin >> q >> i >> j >> k;
        if (q==1) qry1.push_back(t3(i,j,k));
        else qry2.push_back(t4(k,i,j,y++));
    }
    sort(all(qry2));
    vector<ll> result(qry2.size());
    for (int i=1, j=0; i<=qry1.size(); ++i) {
        int l,r,k; tie(l,r,k) = qry1[i-1];

        tree.update(tree.tree, k, l, r);
        while (j<qry2.size() && i == get<0>(qry2[j])){
            int ii,ll,rr,xx; tie(ii,ll,rr,xx) = qry2[j++];
            result[xx] = tree.query(tree.tree, ll, rr);
        }
    }

    for (auto x : result) cout << x << '\n';
} // namespace std;
