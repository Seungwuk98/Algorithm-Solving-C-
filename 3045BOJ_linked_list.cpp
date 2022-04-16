#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using ll = long long;
using namespace std;

struct Node
{
    Node *l, *r, *p;
    ll val;
    int cnt; bool inv;
    Node(){
        l=r=p=nullptr;
        val=0;
        cnt=1; inv = 0;
    }
};


struct SplayTree
{
    Node *tree;
    Node *dummyL;
    Node *dummyR;
    int length = 0;
    vector<Node*> ptr;

    void rotate(Node *x){
        Node *p = x->p;
        prop(p); prop(x);
        Node *a;
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
            if (g){
                rotate((g->l == p) == (p->l == x) ? p : x);
            }
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

    void flip(int l, int r){
        interval(l,r);
        Node *x = tree->r->l;
        x->inv = !x->inv;
    }

    void shift(int l, int r, int z){
        z %= (r-l+1);
        if (z<0) z+= (r-l+1);
        if (!z) return;
        flip(l,r-z); flip(r-z+1, r); flip(l,r);
    }

    void prop(Node *x){
        if (!x->inv) return;
        swap(x->l, x->r);
        if (x->l) x->l->inv = !x->l->inv;
        if (x->r) x->r->inv = !x->r->inv;
        x->inv = 0;
    }

    void kth(int k){
        Node *x = tree;
        prop(x);
        while (1){
            while (x->l && x->l->cnt > k) {
                x = x->l;
                prop(x);
            } 
            if (x->l) k -= x->l->cnt;
            if (!k--) break;
            x = x->r;
            prop(x);
        }
        splay(x);
    }

    void add(int i, ll z){
        kth(i);
        tree->val += z;
    }


    void init(int n){
        length = n;
        tree = dummyL = new Node();
        Node *pre = dummyL;
        pre->cnt = n+2;
        for (int i=1; i<=n; ++i){
            Node *node = new Node();
            node->cnt = n+2-i;
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
            kth(i); cout << tree->val << ' ';
        }
        cout << '\n';
    }

    bool check(){
        Node *x = tree;
        while (x->r) x=x->r;
        return x == dummyR;
    }

    void push(){
        for (int i=1; i<=length; ++i) kth(i);
    }
}tree;

int n, q;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    tree.init(n);
    for (int i=1; i<=n; ++i) tree.add(i,i);
    while (q--){
        int z,x,y; cin >> z >> x >> y;
        if (z==1){
            tree.shift(1,y,y-x+1);
        } else if(z==2){
            tree.shift(x,n,-y+x-1);
        } else{
            tree.shuffle(x,y);
        }
    }
    tree.print();
}