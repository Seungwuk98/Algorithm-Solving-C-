#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#define all(v) v.begin(), v.end()


using ll = long long;
using namespace std;

struct Node
{
    Node *l, *r, *p;
    bool val, fil, inv;
    int sum, lmax, rmax, max;
    int cnt;
    Node(){
        l=r=p=nullptr;
        val=0; inv=0;
        sum=lmax=rmax=max=0;
        cnt=1;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};


struct SplayTree
{
    Node *tree;
    Node *dummyL;
    Node *dummyR;
    int length = 0;

    SplayTree(){
        tree = nullptr;
    }
    ~SplayTree(){
        if (tree) delete tree;
    }

    void rotate(Node *x){
        Node *p = x->p;
        Node *a;
        prop(p); prop(x);
        if (p->l == x){
            p->l = a = x->r;
            x->r = p;
        } else{
            p->r = a = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (a) a->p = p;
        (x->p ? x->p->l == p ? x->p->l : x->p->r : tree) = x;
        update(p);
        update(x);
    }

    void splay(Node *x){
        while (x->p){
            Node *p = x->p;
            Node *g = p->p;            
            if (g) rotate((g->l == p) == (p->l == x) ? p : x);
            rotate(x);
        }
    }

    void merge(Node *ret, Node *l, Node *r){
        int lmax, rmax, mx, sm, cnt;
        bool fil;
        fil = l->fil && r->fil;
        sm = l->sum + r->sum;
        cnt = l->cnt + r->cnt;
        lmax = l->fil? l->sum + r->lmax : l->lmax;
        rmax = r->fil? r->sum + l->rmax : r->rmax;
        mx = max({l->max, r->max, l->rmax + r->lmax});
        ret->lmax = lmax;
        ret->rmax = rmax;
        ret->max = mx;
        ret->sum = sm;
        ret->fil = fil;
        ret->cnt = cnt;
    }

    void update(Node *x){
        x->fil = x->sum = x->max = x->lmax = x->rmax = x->val;
        x->cnt = 1;
        if (x->l) {
            prop(x->l);
            merge(x, x->l, x);
        } 
        if (x->r) {
            prop(x->r);
            merge(x, x, x->r);
        }
    }

    void kth(int k){
        Node *x = tree;
        prop(x);
        while (1){
            while (x->l && x->l->cnt > k) {
                x = x->l; prop(x);
            } 
            if (x->l) k -= x->l->cnt;
            if (!k--) break;
            x = x->r; prop(x);
        }
        splay(x);
    }

    void change(int i, bool z){
        kth(i);
        tree->val = z;
        update(tree);
    }

    void flip(int l, int r){
        interval(l,r);
        Node *x = tree->r->l;
        x->inv = !x->inv;
        prop(x);
        while (x->p){
            x=x->p; update(x);
        }
    }

    void prop(Node *x){
        if (!x->inv) return;
        swap(x->l, x->r);
        swap(x->lmax, x->rmax);
        if (x->l) x->l->inv = !x->l->inv;
        if (x->r) x->r->inv = !x->r->inv;
        x->inv = 0;
    }

    void init(int n){
        length = n;
        tree = dummyL = new Node();
        Node *pre = dummyL;
        pre->cnt = n+2;
        while (n--){
            Node *node = new Node();
            node->cnt = n+2;
            pre->r = node;
            node->p = pre;
            pre = node;
        }
        dummyR = new Node();
        dummyR->cnt = 1;
        pre->r = dummyR;
        dummyR->p = pre;
    }

    void interval(int l, int r){
        kth(l-1);
        Node *x = tree;
        tree = x->r;
        tree->p = nullptr;
        kth(r-l+1);
        x->r = tree;
        tree->p = x;
        tree = x;
    }


    void print(){
        for (int i=1; i<=length; ++i){
            kth(i); cout << tree->val;
        }
        cout << '\n';
    }

    int query(int l, int r){
        interval(l,r);
        return tree->r->l->max;
    }

}tree;

int n, q;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    tree.init(n);
    for (int i=1; i<=n; ++i) {
        bool x; cin >> x;
        tree.change(i, x);
    }
    cin >> q;
    while (q--){
        int x, l, r; cin >> x >> l >> r;
        if (x == 1) tree.flip(l,r);
        else cout << tree.query(l,r) << '\n';
    }

}