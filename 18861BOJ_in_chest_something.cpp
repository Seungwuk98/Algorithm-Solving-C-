#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF 1'000'000'001

using namespace std;
using pii = pair<int, int>;


struct LCT {
    struct Node
    {
        Node *l, *r, *p;
        bool inv;
        int id, val;
        pii mn;
        Node() {
            l = r = p = nullptr;
            inv = 0;
            id = -1;
            val = INF;
            mn = {INF,-1};
        }

    };
    
    vector<Node> node;
    int t;

    bool isRoot(Node *x) {
        return (!x->p || (x->p->l != x && x->p->r != x));
    }

    void update(Node *x) {
        x->mn = {x->val, x->id};
        if (x->l) x->mn = min(x->mn, x->l->mn);
        if (x->r) x->mn = min(x->mn, x->r->mn);
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
        update(p); update(x);
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

    void link(Node *x, Node *y) {
        access(x); access(y);
        x->l = y;
        y->p = x;
        update(x);
    }

    void cut(Node *x) {
        access(x);
        if (!x->l) return;
        x->l->p = nullptr;
        x->l = nullptr;
        update(x);
    }

    Node *lca(Node *x, Node *y) {
        access(x); return access(y);
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

    pii query(Node *x, Node *y) {
        Node *p = lca(x, y);
        pii mn = {p->val, p->id};
        access(x);
        splay(p);
        if (p->r) mn = min(mn, p->r->mn);
        access(y);
        splay(p);
        if (p->r) mn = min(mn, p->r->mn);
        return mn;
    }

    void makeRoot(Node *x) {
        access(x);
        x->inv ^= 1;
        prop(x);
    }

    void connect(Node *x, Node *y) {
        makeRoot(x);
        link(x, y);
    }

    void set(Node *x, int val) {
        access(x);
        x->val = val;
        update(x);
    }

    LCT(int cap, int n) {
        node.resize(cap);
        for (int i=0; i<cap; ++i) {
            node[i].id = i;
        }
        t = n+1;
    }

    void makeEdge(Node *u, Node *v, int c) {
        node[t].val = c;
        node[t].mn = {c, t};
        connect(u, &node[t]);
        connect(&node[t], v);
        t++;
    }

    void cutEdge(Node *u, Node *v) {
        if (parent(u) != v) swap(u, v);
        cut(u);
    }

    int lca(int u, int v) {return lca(&node[u], &node[v])->id;}
    void cut(int u) {cut(&node[u]);}
    void link(int u, int v) {link(&node[u], &node[v]);}
    void connect(int u, int v) {connect(&node[u], &node[v]);}
    pii query(int u, int v) {return query(&node[u], &node[v]);}
    void set(int u, int v) {set(&node[u], v);}
    bool linked(int u, int v) {return findRoot(&node[u]) == findRoot(&node[v]);}
    void makeEdge(int u, int v, int c) {makeEdge(&node[u], &node[v], c);}
    void cutEdge(int u, int v) {cutEdge(&node[u], &node[v]);}
} ;


int main()
{
    fastio
    multiset<pii> C;
    vector<pii> E;
    int n,m; cin >> n >> m;
    LCT lct(2*n + m + 10, n);

    int op, x, y, z;
    while (m--) {
        cin >> op >> x;
        if (op == 1) {
            cin >> y >> z;
            if (lct.linked(x, y)) {
                auto [mn, id] = lct.query(x, y);
                if (z > mn) {
                    auto [v1, v2] = E[id-n-1];
                    lct.cutEdge(v1, id);
                    lct.cutEdge(v2, id);
                    C.insert({z,lct.t});
                    E.push_back({x, y});
                    lct.makeEdge(x, y, z);
                }
            } else {
                C.insert({z, lct.t});
                E.push_back({x, y});
                lct.makeEdge(x, y, z);
            }
        } else if (op == 2) {
            for (auto [w, id] : C) {
                if (w >= x) break;
                auto [v1, v2] = E[id-n-1];
                lct.cutEdge(v1, id);
                lct.cutEdge(v2, id);
                C.erase({w, id});
            }
        } else {
            cin >> y;
            if (lct.linked(x, y)) cout << lct.query(x, y).first << '\n';
            else cout << 0 << '\n';
        }
    }

} // namespace std;
