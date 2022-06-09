#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct Node {
    Node *l, *r, *p, *pp;
    int i;
    bool inv;

    Node() {
        l = r = p = pp = nullptr;
    }
} *node[101010];

void prop(Node *x) {
    if (x->inv) {
        swap(x->l, x->r);
        x->inv = 0;
        if (x->l) x->l->inv = !x->l->inv;
        if (x->r) x->r->inv = !x->r->inv;
    }
}

void rotate (Node *x) {
    Node *p = x->p, *a;
    prop(p); prop(x);
    if (p->l == x) {
        p->l = a = x->r;
        x->r = p;
    } else {
        p->r = a = x->l;
        x->l = p;
    }
    x->p = p->p;
    p->p = x;
    if (a) a->p = p;
    if (x->p) {
        if (x->p->l == p) x->p->l = x;
        else if (x->p->r == p) x->p->r = x;
    } 
    else {
        x->pp = p->pp;
        p->pp = nullptr;
    }
}

void splay (Node *x) {
    while (x->p) {
        assert(x != x->p->p);
        Node *p = x->p, *g = p->p;
        if (g) rotate((p->l == x) == (g->l == p) ? p : x);
        rotate(x);
    }
}

void access(Node *x) {
    splay(x);
    prop(x);
    if (x->r) {
        x->r->pp        = x;
        x->r->p         = nullptr;
        x->r            = nullptr;
    }
    while (x->pp) {
        Node *pp = x->pp;
        splay(pp);
        prop(pp);
        if (pp->r) {
            pp->r->pp       = pp;
            pp->r->p        = nullptr;
        }
        pp->r   = x;
        x->p    = pp;
        x->pp   = nullptr;
        splay(x);
    }
}

Node *find_root(Node *x) {
    access(x);
    while (x->l) {
        x = x->l;
        prop(x);
    } 
    access(x);
    return x;
}

void make_root(Node *x) {
    access(x); 
    x->inv = !x->inv;
    prop(x);
}

void link(Node *root, Node *x) {
    access(root); 
    access(x);
    root->l = x;
    x->p = root;
}

void connect(Node *x, Node *t) {
    make_root(x);
    link(x, t);
}

void cut(Node *x) {
    access(x);
    if (x->l) {
        x->l->p = nullptr;
        x->l    = nullptr;
    }
}


Node *lca(Node *x, Node *t) {
    access(x); access(t);
    splay(x);
    return x->pp ? x->pp : x;
}

int main() {
    fastio
    int n, m; cin >> n >> m;
    for (int i=1; i<=n; ++i) {
        node[i] = new Node();
        node[i]->i = i;
    } 
    
    int op, a, b;
    while (m--) {
        cin >> op >> a >> b;
        if (a > b) swap(a,b);
        if (op == 1) {
            connect(node[a], node[b]);
        } else if (op == 2) {
            cut(node[a]);
        } else {
            Node *pa = find_root(node[a]);
            Node *pb = find_root(node[b]);
            cout << (pa == pb) << '\n';
        }
    }
}