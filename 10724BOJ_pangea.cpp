#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

struct Node {
    Node *l, *r, *p;
    int id;
    int val, mx, mxid;
    int u, v;
    bool inv;
    Node()
     : l(nullptr), r(nullptr), p(nullptr),
       inv(0), val(-1), mx(0), mxid(-1), u(-1), v(-1) {}
} *node[202020];

inline bool is_root(Node *x) {
    return (!x->p || (x->p->l != x && x->p->r != x));
}

void update(Node *x) {
    x->mx = x->val;
    x->mxid = x->id;
    if (x->l) {
        if (x->l->mx > x->mx) {
            x->mx = x->l->mx;
            x->mxid = x->l->mxid;
        }
    } 
    if (x->r) {
        if (x->r->mx > x->mx) {
            x->mx = x->r->mx;
            x->mxid = x->r->mxid;
        }
    } 
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
    int mx = p->val;
    int mxid = p->id;
    access(x);
    splay(p);
    if (p->r) {
        if (p->r->mx > mx) {
            mx = p->r->mx;
            mxid = p->r->mxid;
        }
    } 

    access(y);
    splay(p);
    if (p->r) {
        if (p->r->mx > mx) {
            mx = p->r->mx;
            mxid = p->r->mxid;
        }
    } 
    return mxid;
}

void point_update(Node *x, int val) {
    access(x);
    x->val = val;
    update(x);
}

struct edge
{
    int u, v, w;
    bool operator<(const edge &o) const {
        return w < o.w;
    }
};




int n, m;


int main() {
    fastio
    int T; cin >> T;
    ll ans = 0;
    while (T--) {
        cin >> n >> m;
        int t = 0;
        for (int i=0; i<n; ++i) {
            node[t] = new Node();
            node[t]->id = t;
            t++;
        }

        int u, v, c;     
        ll ret = 0;   
        for (int i=1; i<=n-1; ++i) {
            cin >> u >> c;
            ret += c;
            node[t] = new Node();
            node[t]->id = node[t]->mxid = t;
            node[t]->val = node[t]->mx = c;
            node[t]->u = i;
            node[t]->v = u;
            connect(node[i], node[t]);
            connect(node[u], node[t]);
        }

        while (m--) {
            cin >> u >> v >> c;
            int mxid = query(node[u], node[v]);
            if (node[mxid]->val > c) {
                cut(node[mxid], node[node[mxid]->u]);
                cut(node[mxid], node[node[mxid]->v]);
                ret += c - node[mxid]->val;
                node[mxid]->val = node[mxid]->mx = c;
                node[mxid]->mxid = node[mxid]->id;
                node[mxid]->u = u;
                node[mxid]->v = v;
                connect(node[u], node[mxid]);
                connect(node[v], node[mxid]);
            }
        }
        ans ^= ret;
        memset(node, 0, sizeof(node));
    }

    cout << ans;
}