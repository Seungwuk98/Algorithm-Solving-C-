#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct Node {
    Node *l, *r, *p;
    int id;
    int sum, val;
    bool inv;
    Node() : l(nullptr), r(nullptr), p(nullptr), inv(0), sum(0), val(0) {}
} *node[101010];

inline bool is_root(Node *x) {
    return (!x->p || (x->p->l != x && x->p->r != x));
}

void update(Node *x) {
    x->sum = x->val;
    if (x->l) x->sum += x->l->sum;
    if (x->r) x->sum += x->r->sum;
}

void prop(Node *x) {
    if (x->inv) {
        swap(x->l, x->r);
        x->inv = 0;
        if (x->l) x->l->inv ^= 1;
        if (x->r) x->r->inv ^= 1;
    }
}

void rotate(Node * x) {
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
    update(p); update(x);
}

void splay(Node * x) {
    prop(x);
    while (!is_root(x)) {
        Node * p = x->p;
        if (!is_root(p)) {
            if ((x == p->l) == (p == p->p->l)) rotate(p);
            else rotate(x);
        }
        rotate(x);
    }
}

Node * access(Node * x) {
    splay(x);
    x->r = nullptr;
    update(x);
    Node * y = x;
    while (x->p) {
        y = x->p;
        splay(y);
        y->r = x;
        update(y);
        splay(x);
    }
    return y;
}

void link(Node * x, Node * y) {
    access(x); access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *parent(Node *x) {
    access(x);
    x = x->l;
    if (!x) return nullptr;
    prop(x);
    while (x->r) {
        x = x->r;
        prop(x);
    } 
    splay(x);
    return x;
}

void cut(Node * x) {
    access(x);
    x->l->p = nullptr;
    x->l = nullptr;
    update(x);
}

void cut(Node *x, Node *y) {
    Node *px = parent(x);
    if (px != y) {
        swap(x, y);
        px = parent(x);
    } 
    if (px == y) cut(x);
}

Node * lca(Node * x, Node * y) {
    access(x);
    return access(y);
}

Node *find_root(Node *x) {
    access(x);
    while (x->l) {
        x = x->l;
        prop(x);
    }
    splay(x); // access(x) ? 
    return x;
}


void make_root(Node *x) {
    access(x);
    x->inv = !x->inv;
    prop(x);
}

void connect(Node *s, Node *p) {
    make_root(s);
    link(s, p);
}

int query(Node *x, Node *y) {
    Node *p = lca(x, y);
    int sum = p->sum;
    access(x);
    splay(p);
    if (p->r) sum += p->r->sum;

    access(y);
    splay(p);
    if (p->r) sum += p->r->sum;
    return sum;

}

int main() {
    fastio
    int n,m; cin >> n >> m;
    for (int i=1; i<=n; ++i) {
        node[i] = new Node();
        node[i]->id = i;
    } 
    int op, u, v;
    while (m--) {
        cin >> op >> u >> v;
        if (op == 1) {
            connect(node[u], node[v]);
        } else if (op == 2) {
            cut(node[u], node[v]);
        } else {
            cout << (find_root(node[u]) == find_root(node[v])) << '\n';
        }
    }
}