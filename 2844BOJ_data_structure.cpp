#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using ll = long long;
using namespace std;

struct Node
{
    Node *l, *r, *p;
    ll val, sum, fst, snd, cng;
    int cnt;
    Node(){
        l=r=p=nullptr;
        val=sum=fst=snd=0;
        cng = -1;
        cnt=1;
    }
};


struct SplayTree
{
    Node *tree;
    Node *dummyL;
    Node *dummyR;
    int length = 0;

    void rotate(Node *x){
        Node *p = x->p;
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
            if (g) rotate((g->l == p) == (p->l == x) ? p : x);
            rotate(x);
        }
    }

    void update(Node *x){
        prop(x);
        x->sum = x->val;
        x->cnt = 1;
        if (x->l){
            prop(x->l);
            x->sum += x->l->sum;
            x->cnt += x->l->cnt;
        } 
        if (x->r) {
            prop(x->r);
            x->sum += x->r->sum;
            x->cnt += x->r->cnt;
        }
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

    void prop(Node *x){
        if (x->cng != -1){
            x->val = x->cng;
            x->sum = x->cnt * x->cng;
            if (x->l){
                x->l->cng = x->cng;
                x->l->fst = x->l->snd = 0;
            }
            if (x->r){
                x->r->cng = x->cng;
                x->r->fst = x->r->snd = 0;
            }
            x->cng = -1;
        }
        if (x->fst || x->snd){
            int sz = x->cnt;
            x->sum += sz * (2*x->fst + (sz-1)*x->snd)/2;
            x->val += x->fst + (x->l? x->l->cnt : 0) * x->snd;
            if (x->l){
                x->l->fst += x->fst;
                x->l->snd += x->snd;
            }
            if (x->r){
                x->r->fst += x->fst + (x->l?x->l->cnt+1:1)*x->snd;
                x->r->snd += x->snd;
            }
            x->fst = x->snd = 0;
        }

    }

    void change(int l, int r, ll z){
        interval(l, r);
        Node *x = tree->r->l;
        x->cng = z;
        x->fst = x->snd = 0;
        prop(x);
    }

    void add(int l, int r, ll z){
        interval(l,r);
        Node *x = tree->r->l;
        x->fst = z;
        x->snd = z;
        prop(x);
    }

    void add(int i, ll z){
        kth(i);
        tree->sum += z;
        tree->val += z;
    }

    void insert(int i, ll z){
        kth(i);
        Node *x = tree->l, *a;
        prop(x);
        while (x->r) {
            x=x->r;
            prop(x);
        }
        x->r = a = new Node();
        a->p = x;
        a->val = a->sum = z;
        update(x);
        while (x->p){
            x=x->p;
            update(x);
        }
    }

    void init(int n){
        length = n;
        tree = dummyL = new Node();
        Node *pre = dummyL;
        while (n--){
            Node *node = new Node();
            pre->r = node;
            node->p = pre;
            pre = node;
        }
        dummyR = new Node();
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


    ll query(int l, int r){
        interval(l,r);
        return tree->r->l->sum;
    }

    void print(){
        for (int i=1; i<=length; ++i){
            kth(i); cout << tree->val << ' ';
        }
        cout << '\n';
    }

}tree;

int n, q;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    tree.init(n);
    for (int i=1; i<=n; ++i) {
        int x; cin >> x;
        tree.add(i,x);
    }
    while (q--){
        int a,b,c; ll x;
        cin >> a;
        if (a==1){
            cin >> b >> c >> x;
            tree.change(b,c,x);
        } else if (a==2){
            cin >> b >> c >> x;
            tree.add(b,c,x);
        } else if (a==3){
            cin >> c >> x;
            tree.insert(c,x);
        } else{
            cin >> b >> c;
            cout << tree.query(b,c) << '\n';
        }
    }


}