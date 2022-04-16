#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF 1000000000000LL

using namespace std;
using ll = long long;
int n, m;
vector<ll> arr;

struct Node
{
    Node *l, *r;
    ll max, smax, sum, lazy;
    int maxcnt;
    Node(){
        l=r=nullptr; 
        max = sum = 0;
        smax = -1;
        maxcnt = 1;
        lazy = INF;
    }
};

struct Segtree
{
    Node *tree;
    void init(int n){
        tree = init(1, n);
    }
    Node* init(int lo, int hi){
        Node *x = new Node();
        if (lo == hi) {
            x->sum = x->max = arr[lo-1];
            return x;
        }
        int mid = lo + hi >> 1;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        if (x->l->max < x->r->max){
            x->max = x->r->max;
            x->maxcnt = x->r->maxcnt;
            x->smax = max(x->l->max, x->r->smax);
        } else if (x->l->max > x->r->max){
            x->max = x->l->max;
            x->maxcnt = x->l->maxcnt;
            x->smax = max(x->l->smax, x->r->max);
        } else {
            x->max = x->l->max;
            x->maxcnt = x->l->maxcnt + x->r->maxcnt;
            x->smax  = max(x->l->smax, x->r->smax);
        }
        x->sum = x->l->sum + x->r->sum;
        return x;
    }

    void prop(Node *x){
        if (x->lazy >= x->max) return;
        x->sum -= (x->max - x->lazy)*x->maxcnt;
        x->max = x->lazy;
        if (x->l && x->r){
            x->l->lazy = min(x->l->lazy, x->lazy);
            x->r->lazy = min(x->r->lazy, x->lazy);    
        }
        x->lazy = INF;
    }

    void update(Node *x, int lo, int hi, int s, int e, ll X){
        prop(x);
        if (hi < s || e < lo || x->max <= X) return;
        if (s <= lo && hi <= e && x->smax < X) {
            x->lazy = X;
            prop(x);
            return;
        }
        int mid = lo + hi >> 1;
        update(x->l, lo, mid, s, e, X); update(x->r, mid+1, hi, s, e, X);
        if (x->l->max < x->r->max){
            x->max = x->r->max;
            x->maxcnt = x->r->maxcnt;
            x->smax = max({x->l->max, x->l->smax, x->r->smax});
        } else if (x->l->max > x->r->max){
            x->max = x->l->max;
            x->maxcnt = x->l->maxcnt;
            x->smax = max({x->l->smax, x->r->max, x->r->smax});
        } else {
            x->max = x->l->max;
            x->maxcnt = x->l->maxcnt + x->r->maxcnt;
            x->smax  = max(x->l->smax, x->r->smax);
        }
        x->sum = x->l->sum + x->r->sum;
    }

    ll query_sum(Node *x, int lo, int hi, int s, int e){
        prop(x);
        if (hi < s || e < lo) return 0;
        if (s <= lo && hi <= e) return x->sum;
        int mid = lo + hi >> 1;
        return query_sum(x->l, lo, mid, s, e) + query_sum(x->r, mid+1, hi, s, e);
    }

    ll query_max(Node *x, int lo, int hi, int s, int e){
        prop(x);
        if (hi < s || e < lo) return 0;
        if (s <= lo && hi <= e) return x->max;
        int mid = lo + hi >> 1;
        return max(query_max(x->l, lo, mid, s, e), query_max(x->r, mid+1, hi, s, e));
    }

} tree;


int main()
{
    fastio
    cin >> n;
    arr.resize(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    tree.init(n);
    cin >> m;
    while (m--){
        int q, l, r; ll x;
        cin >> q >> l >> r;
        if (q==1){
            cin >> x;
            tree.update(tree.tree, 1, n, l, r, x);
        } else if (q==2){
            cout << tree.query_max(tree.tree, 1, n, l, r) << '\n';
        } else{
            cout << tree.query_sum(tree.tree, 1, n, l, r) << '\n';
        }
    }
} // namespace std;
