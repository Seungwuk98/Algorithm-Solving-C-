#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#define all(v) v.begin(), v.end()


using ll = long long;
using namespace std;

struct Node
{
    Node *l, *r, *p;
    ll val; bool inv;
    int cnt;
    Node(){
        l=r=p=nullptr;
        val=0; inv=0;
        cnt=1;
    }
    ~Node(){
        if(l) delete l;
        if(r) delete r;
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

    void update(Node *x){
        x->cnt = 1;
        if (x->l){
            x->cnt += x->l->cnt;
        } 
        if (x->r) {
            x->cnt += x->r->cnt;
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

    void add(int i, ll z){
        kth(i);
        tree->val += z;
    }

    void flip(int l, int r){
        interval(l,r);
        Node *x = tree->r->l;
        x->inv = !x->inv;
        prop(x);
    }

    void prop(Node *x){
        if (!x->inv) return;
        swap(x->l, x->r);
        if (x->l) x->l->inv = !x->l->inv;
        if (x->r) x->r->inv = !x->r->inv;
        x->inv = 0;
    }

    void init(int n){
        if (tree) delete(tree);
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

    void query(Node *x, int &count){
        splay(x); int k = tree->l->cnt;
        cout << k << ' ';
        flip(count++, k);
    }

    void print(){
        for (int i=1; i<=length; ++i){
            kth(i); cout << tree->val;
        }
        cout << '\n';
    }

}tree;


struct p
{
    int x, idx; Node* y;
    bool operator< (const p &t) const{
        if (x != t.x) return x < t.x;
        return idx < t.idx;
    }
};

vector<p> ptr;
void solve(int n){
    tree.init(n);
    ptr.clear();
    for (int i=1; i<=n; ++i){
        int x; cin >> x;
        tree.add(i,x); ptr.push_back(p{x,i,tree.tree});
    }
    sort(all(ptr));
    int count = 1;
    for (auto &x : ptr){
        tree.query(x.y, count);
    }
    cout << '\n';

}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (1){
        int n; cin >> n; if(!n) break;
        solve(n);
    }
}