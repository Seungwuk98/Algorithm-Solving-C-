#include <bits/stdc++.h>
#define INF 2147483647
using namespace std;

struct Node{
    int cnt;
    Node *l, *r;
    Node(){
        cnt = 0;
        l=r=nullptr;
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

    void clear(){
        if (tree) delete tree;
        tree = new Node();
    }

    void update(Node *x, int w, int s=-INF-1, int e=INF){
        if (s==e){
            x->cnt++; return;
        }
        int mid = s + e >> 1;
        if (w <= mid){
            if (!x->l) x->l = new Node();
            update(x->l, w, s, mid);
        } else {
            if (!x->r) x->r = new Node();
            update(x->r, w, mid+1, e);
        }
        x->cnt = (x->l? x->l->cnt:0) + (x->r? x->r->cnt:0);
    }

    int query(Node *x, int k, int s=-INF-1, int e=INF){
        if (s==e) return s;
        int mid = s+e>>1;
        int diff = x->l? x->l->cnt : 0;
        if (k>diff) return query(x->r, k-diff, mid+1, e);
        else return query(x->l, k, s, mid);
    }

} tree;



int main()
{
    int T; cin >> T;
    while (T--){
        int n; cin >> n;
        tree.clear();
        vector<int> result;
        for (int i=0; i<n; ++i){
            int x; cin >> x;
            tree.update(tree.tree, x);
            if (~i&1) result.push_back(tree.query(tree.tree, i/2+1));
        }
        int l = result.size();
        cout << l << '\n';
        for (int i=0; i<l; ++i){
            cout << result[i] << ' ';
            if (i%10==9) cout << '\n';
        }
        if (l%10) cout << '\n';
        
    }
} // namespace std;
