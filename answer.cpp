#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int inf = 1e9+7;

int arr[1010101];

struct Node{
    Node *l, *r, *p;
    ll v, sz, sum, mx, mn;
    bool dummy, flip;

    Node(ll _v, Node *p) : v(_v), p(p) {
        l = r = nullptr;
        sum = mx = mn = _v;
        sz = 1, dummy = 0, flip = 0;
    }
    Node(int _v) : Node(_v, nullptr) {}
    Node() : Node(0) {}
    ~Node(){
        if(l) delete l;
        if(r) delete r;
    }
};

struct SplayTree{
    Node *root;
    Node *ptr[1010101]; //node pointer

    void update(Node *x){
        x->sz = 1;
        x->sum = x->mn = x->mx = x->v;
        if(x->l){
            x->sz += x->l->sz;
            x->sum += x->l->sum;
            x->mn = min(x->mn, x->l->mn);
            x->mx = max(x->mx, x->l->mx);
        }
        if(x->r){
            x->sz += x->r->sz;
            x->sum += x->r->sum;
            x->mn = min(x->mn, x->r->mn);
            x->mx = max(x->mx, x->r->mx);
        }
    }

    void push(Node *x){
        if(!x->flip) return;
        swap(x->l, x->r);
        if(x->l) x->l->flip = !x->l->flip;
        if(x->r) x->r->flip = !x->r->flip;
        x->flip = 0;
    }

    Node* gather(int s, int e){ //gather [s, e]
        kth(e+1);
        auto tmp = root;
        kth(s-1);
        splay(tmp, root);
        return root->r->l;
    }

    void rotate(Node *x){
        auto p = x->p;
        Node *y;
        push(p); push(x);
        if(x == p->l){
            p->l = y = x->r;
            x->r = p;
        }else{
            p->r = y = x->l;
            x->l = p;
        }
        x->p = p->p; p->p = x;
        if(y) y->p = p;
        if(x->p){
            if(p == x->p->l) x->p->l = x;
            else x->p->r = x;
        }
        else root = x;
        update(p); update(x);
    }

    void splay(Node *x, Node *g = nullptr){
        Node *y;
        while(x->p != g){
            Node *p = x->p;
            if(p->p == g){
                rotate(x); break;
            }
            auto pp = p->p;
            if((p->l == x) == (pp->l == p)){
                rotate(p); rotate(x);
            }else{
                rotate(x); rotate(x);
            }
        }
        if(!g) root = x;
    }

    SplayTree() : root() {
        memset(ptr, 0, sizeof ptr);
    }
    ~SplayTree(){
        if(root) delete root;
    }

    void init(int n){
        if(root) delete root;
        root = new Node(-inf); //left dummy node
        auto now = root;
        for(int i=1; i<=n; i++){
            ptr[i] =  now->r = new Node(i, now);
            now = now->r;
        }
        now->r = new Node(inf, now); //right dummy node
        root->dummy = now->r->dummy = 1;
        for(int i=n; i>=1; i--) update(ptr[i]);
        splay(ptr[n/2]);
    }

    void flip(int s, int e){
        Node *x = gather(s, e);
        x->flip = !x->flip;
    }

    void shift(int s, int e, int k){
        Node *x = gather(s, e);
        cout << x->mn << " " << x->mx << " " << x->sum << "\n";
        if(k >= 0){
            k %= (e - s + 1);
            if(!k) return;
            flip(s, e); flip(s, s+k-1); flip(s+k, e);
        }else{
            k *= -1;
            k %= (e - s + 1);
            if(!k) return;
            flip(s, e); flip(s, e-k); flip(e-k+1, e);
        }
    }

    void getidx(int k){
        splay(ptr[k]);
        cout << root->l->sz << "\n";
    }

    void kth(int k){ //1-based
        auto now = root;
        push(now);
        while(1){
            while(now->l && now->l->sz > k){
                now = now->l; push(now);
            }
            if(now->l) k -= now->l->sz;
            if(!k) break; k--;
            now = now->r;
            push(now);
        }
        splay(now);
    }

    void print(Node *x){
        push(x);
        if(x->l) print(x->l);
        if(!x->dummy) cout << x->v << " ";
        if(x->r) print(x->r);
    }
}tree;

int n, m, q;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    tree.init(n);
    while(q--){
        int op; cin >> op;
        if(op == 1){
            int s, e; cin >> s >> e;
            tree.flip(s, e);
            Node *x = tree.gather(s, e);
            cout << x->mn << " " << x->mx << " " << x->sum << "\n";
        }else if(op == 2){
            int s, e, k; cin >> s >> e >> k;
            tree.shift(s, e, k);
        }else if(op == 3){
            int k; cin >> k;
            tree.kth(k);
            cout << tree.root->v << "\n";
        }else if(op == 4){
            int k; cin >> k;
            tree.getidx(k);
        }
    }
        tree.print(tree.root);
        cout << '\n';
}