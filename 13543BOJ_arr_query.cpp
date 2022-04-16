#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


using ll = unsigned int;
using namespace std;
ll comb[11][11] = {1};

ll mpow(ll z, int i){
    ll ret = 1;
    while (i){
        if (i&1) ret *= z;
        z*=z;
        i>>=1;
    }
    return ret;
}


struct Node
{
    Node *l, *r, *p;
    ll val, sum[11];
    int cnt;
    Node(){
        l=r=p=nullptr;
        val=0;
        fill(&sum[0], &sum[11],0);
        cnt=1;
    }
    Node(Node *p, ll val) : p(p), val(val){
        l=r=nullptr;
        fill(&sum[0], &sum[11], val);
        cnt = 1;
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
            for (int i=0; i<=10; ++i) x->sum[i] = x->l->sum[i] + x->val * mpow(x->cnt, i);
            if (x->r) {
                for (int i=0; i<=10; ++i) for (int t=0; t<=i; ++t) 
                    x->sum[i] += x->r->sum[t] * mpow(x->cnt, i-t) * comb[i][t];
                x->cnt += x->r->cnt;
            }
        } else if (x->r){
            fill(&x->sum[0], &x->sum[11], x->val);
            x->cnt += x->r->cnt;
            for (int i=0; i<=10; ++i) for (int t=0; t<=i; ++t)
                x->sum[i] += x->r->sum[t]*comb[i][t];
        } else {
            fill(&x->sum[0], &x->sum[11], x->val);
        }
    }

    void kth(int k){
        Node *x = tree;
        while (1){
            while (x->l && x->l->cnt > k) {
                x = x->l;
            } 
            if (x->l) k -= x->l->cnt;
            if (!k--) break;
            x = x->r;
        }
        splay(x);
    }

    void insert(int i, ll z){
        kth(i);
        length++;
        Node *x = tree->l;
        while (x->r) x=x->r;
        x->r = new Node(x, z);
        update(x);
        while (x->p){
            x=x->p; update(x);
        }
    }

    void remove(int i){
        kth(i);
        length--;
        Node *r = tree->r, *l = tree->l;
        l->p = tree->l = tree->r = nullptr;
        delete tree;
        tree = l;
        while (l->r) l=l->r;
        l->r = r;
        r->p = l;
        update(l);
        while (l->p){
            l=l->p; update(l);
        }
    }

    void change(int i, ll z){
        kth(i);
        tree->val = z;
        update(tree);
    }

    void add(int i, ll z){
        kth(i);
        tree->val += z;
        update(tree);
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

    ll query(int l, int r, int k){
        interval(l,r);
        return tree->r->l->sum[k];
    }

    void print(){
        for (int i=1; i<=length; ++i){
            kth(i); cout << tree->val << ' ';
        }
        cout << '\n';
    }

}tree;

int main(){
    fastio
    fill(&comb[0][0], &comb[10][11],1);
    for (int i=0; i<11; ++i) for (int j=1; j<i; ++j) comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    int n; cin >> n;
    tree.init(n);
    for (int i=1; i<=n; ++i) {
        ll x; cin >> x;
        tree.add(i, x);
    }
    int m; cin >> m;
    while (m--){
        int t,l,r,k; ll x;
        cin >> t;
        if (t==1){
            cin >> l >> x;
            tree.insert(++l, x);
        } else if (t==2){
            cin >> l;
            tree.remove(++l);
        } else if (t==3){
            cin >> l >> x;
            tree.change(++l, x);
        } else {
            cin >> l >> r >> k;
            cout << tree.query(++l, ++r, k) << '\n';
        }
    }

}