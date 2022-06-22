#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    Node *l, *r, *p;
    bool inv;
    int id, val;
    Node() {
        l = r = p = nullptr;
        inv = 0;
        id = 0;
        val = 1;
    }
} node[101010];

inline bool isRoot(Node *x) {
    return (!x->p || (x->p->l != x && x->p->r != x));
}

void prop(Node *x) {
    if (x->inv) {
        swap(x->l, x->r);
        x->inv = 0;
        if (x->l) x->l->inv ^= 1;
        if (x->r) x->r->inv ^= 1;
    }
}

void rotate(Node *x) {
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
}

void splay(Node *x) {
    prop(x);
    while (!isRoot(x)) {
        Node *p = x->p;
        assert(x != p->p);
        if (!isRoot(p)) rotate((p->l == x) == (p->p->l == p) ? p : x);
        rotate(x);
    }
}

Node *access(Node * x) {
    splay(x);
    x->r = nullptr;
    Node * y = x;
    while (x->p) {
        y = x->p;
        splay(y);
        y->r = x;
        splay(x);
    }
    return y;
}

void link(Node *x, Node *y) {
    access(x); access(y);
    x->l = y;
    y->p = x;
}

void cut(Node *x) {
    access(x);
    if (!x->l) return;
    x->l->p = nullptr;
    x->l = nullptr;
}

Node *findRoot(Node *x) {
    access(x);
    while (x->l) {
        x = x->l;
        prop(x);
    }
    splay(x);
    return x;
}

Node *parent(Node *x) {
    access(x);
    x = x->l;
    if (!x) return nullptr;
    prop(x);
    while (x->r) {
        x = x->r; prop(x);
    }
    splay(x);
    return x;
}

void makeRoot(Node *x) {
    access(x); x->inv ^= 1;
    prop(x);
}

void connect(Node *x, Node *y) {
    makeRoot(x);
    link(x, y);
}

void cut(Node *x, Node *y) {
    if (parent(x) != y) swap(x, y);
    cut(x);
}

using pii = pair<int, int>;
int n, m, q;
pii edge[101010];
int sm[101010] = {0,};
int on[101010] = {0,};

void linkEdge(int i) {
    auto [u, v] = edge[i];
    Node *ru = findRoot(&node[u]);
    Node *rv = findRoot(&node[v]);
    int val = ru->val + rv->val - sm[i];
    connect(&node[u], &node[v]);
    Node *r = findRoot(&node[u]);
    r->val = val;
    on[i] = 1;
}

void cutEdge(int i) {
    auto [u, v] = edge[i];
    Node *r = findRoot(&node[u]);
    int val = r->val;
    cut(&node[u], &node[v]);
    Node *ru = findRoot(&node[u]);
    Node *rv = findRoot(&node[v]);
    ru->val = rv->val = val;
    sm[i] = val;
    on[i] = 0;
}

int main(){
    fastio
    cin >> n >> m >> q;
    int x, y;
    for (int i=1; i<=n; ++i) node[i].id = i;
    for (int i=1; i<n; ++i) {
        cin >> x >> y;
        edge[i] = {x, y};
    }
    while (m--) {
        int D; cin >> D;
        if (on[D]) {
            cutEdge(D);
        } else {
            linkEdge(D);
        }
    }
    while (q--) {
        int c; cin >> c;
        cout << findRoot(&node[c])->val << '\n';
    }
}