#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = unsigned long long;

int n, m;
vector<int> sz, dep, pr, in, top;
vector<bool> vst; 
vector<vector<int>> g;

void dfs1(int node = 1){
    int msz, midx; msz=midx=0;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        dep[next] = dep[node] + 1;
        pr[next] = node;
        dfs1(next); sz[node] += sz[next];
        if (sz[next] > msz){
            msz = sz[next]; midx = i;
        }
    }
    if (!g[node].empty()) swap(g[node][0], g[node][midx]);
}

int pv = 0;

void dfs2(int node = 1){
    in[node] = pv++;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        top[next] = i? next : top[node];
        dfs2(next);
    }
}

struct Node
{
    Node *l, *r;
    ll sum;
    int lo, hi, lazy;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        l=r=nullptr;
        sum=lazy=0;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};

struct Segtree
{
    Node *tree;
    void init(int n){
        tree = init(0,n-1);
    }
    Node* init(int lo, int hi){
        Node *x = new Node(lo, hi);
        if (lo == hi) return x;
        int mid = lo + hi >> 1;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        return x;
    }

    void add(int l, int r){
        add(tree, l, r);
    }

    ll query(int l, int r){
        return query(tree, l, r);
    }

private:
    void prop(Node *x){
        if (!x->lazy) return;
        x->sum += ( x->hi - x->lo + 1) * x->lazy;
        if (x->l && x->r){
            x->l->lazy+=x->lazy;
            x->r->lazy+=x->lazy;
        }
        x->lazy = 0;
    }

    void add(Node *x, int l, int r){
        if (x->lo == l && x->hi == r){
            x->lazy++; prop(x); return;
        }
        prop(x);
        int mid = x->lo + x->hi >> 1;
        if (r<=mid){
            add(x->l, l, r);
            prop(x->r);
        } 
        else if (l>mid) {
            prop(x->l);
            add(x->r, l, r);
        }
        else{
            add(x->l, l, mid);
            add(x->r, mid+1, r);
        }
        x->sum = x->l->sum + x->r->sum;
    }

    ll query(Node *x, int l, int r){
        prop(x);
        if (x->lo == l && x->hi == r) return x->sum;
        int mid = x->lo + x->hi >> 1;
        if (r <= mid){
            return query(x->l, l, r);
        } else if (l > mid){
            return query(x->r, l, r);
        } else {
            return query(x->l, l, mid) + query(x->r, mid+1, r);
        }
    }

} tree;


ll query(int u, int v){
    ll ret=0;
    while (top[u] != top[v]){
        if (dep[top[u]] < dep[top[v]]) swap(u,v);
        int st = top[u];
        ret += tree.query(in[st], in[u]);
        u = pr[st];
    }
    if (u == v) return ret;
    if (dep[u] > dep[v]) swap(u,v);
    ret += tree.query(in[u]+1, in[v]);
    return ret;
}

void update(int u, int v){
    while (top[u] != top[v]){
        if (dep[top[u]] < dep[top[v]]) swap(u,v);
        int st = top[u];
        tree.add(in[st], in[u]);
        u = pr[st];
    }
    if (u==v) return;
    if (dep[u] > dep[v]) swap(u,v);
    tree.add(in[u]+1, in[v]);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    tree.init(n);
    sz.resize(n+1,1); dep.resize(n+1); pr.resize(n+1); in.resize(n+1);
    top.resize(n+1,1); g.resize(n+1);
    vst.resize(n+1);
    for (int i=0; i<n-1; ++i){
        int x,y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    vst[1] = 1;
    dfs1();
    vst.assign(n+1,0); vst[1] = 1;
    dfs2();
    while (m--){
        string x; int u,v;
        cin >> x >> u >> v;
        if (x=="P") update(u,v);
        else cout << query(u,v) << '\n';
    }

} // namespace std;
