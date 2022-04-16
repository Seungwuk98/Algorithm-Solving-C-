#include <iostream>
#include <algorithm>
#include <vector>
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
vector<ll> arr, narr;
int n, q;

struct Node
{
    Node *l, *r;
    int cnt, lo, hi;
    Node(int lo, int hi) : lo(lo), hi(hi){
        l = r = nullptr;
        cnt = 0;
    }
};


struct PST
{
    vector<Node*> roots;
    int last=0;
    void init(int n){
        roots.resize(n+1);
        roots[0] = init(0, n-1);
    }
    void update(int i){
        roots[++last] = new Node(0, n-1);
        update(roots[last-1], roots[last], i);
    }

    int query(int l, int r, int k){
        return query(roots[l-1], roots[r], k);
    }
private:
    Node* init(int lo, int hi){
        Node* x = new Node(lo, hi);
        if (lo == hi) return x;
        int mid = lo + hi >> 1;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        return x;
    }

    void update(Node *p, Node *x, int i){
        if (x->lo == x->hi) {
            x->cnt++; return;
        }
        int mid = x->lo + x->hi >> 1;
        if (i <= mid){
            x->l = new Node(x->lo, mid);
            x->r = p->r;
            update(p->l, x->l, i);
        } else {
            x->r = new Node(mid+1, x->hi);
            x->l = p->l;
            update(p->r, x->r, i);
        }
        x->cnt = x->l->cnt + x->r->cnt;
    }

    int query(Node *l, Node *r, int k){
        if (r->lo == r->hi) return r->lo;
        int diff = r->l->cnt - l->l->cnt;
        if (k>diff) return query(l->r, r->r, k-diff);
        else return query(l->l, r->l, k);
    }
    
} tree ;



int main()
{
    fastio
    cin >> n >> q;
    arr.resize(n);
    narr.resize(n);
    tree.init(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    vector<ll> tmp = arr;
    sort(all(tmp));
    for (ll &x : arr) {
        int i = lower_bound(all(tmp), x) - tmp.begin();
        narr[i] = x;
        tree.update(i);
    }

    while (q--){
        int l, r, k; cin >> l >> r >> k;
        cout << narr[tree.query(l,r,k)] << '\n';
    }

} // namespace std;l
