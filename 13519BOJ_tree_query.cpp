#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF 1000000

using namespace std;
using ll = long long;
int n, m, pv = 0;
vector<int> dep, pr, in, top, sz;
vector<vector<int>> g;
vector<bool> vst;
vector<ll> arr, narr;

struct Node
{
    ll sum, rmax, lmax, max;
    ll lazy;
    Node(){
        sum = 0;
        rmax = lmax = max = 0;
        lazy = INF;
    }
    Node(ll x){
        sum = x;
        if (x > 0) rmax = lmax = max = x;
        else rmax = lmax = max = 0;
        lazy = INF;
    }

    void set(ll x){
        rmax = lmax = max = x;
    }
};

Node tree[404040];

Node mrg(Node a, Node b){
    Node ret;
    ret.sum = a.sum + b.sum;
    ret.lmax = max(a.lmax, a.sum + b.lmax);
    ret.rmax = max(b.rmax, b.sum + a.rmax);
    ret.max = max({a.max, b.max, a.rmax + b.lmax});
    return ret;
}

void init(int x, int s, int e){
    if (s==e) {
        tree[x] = Node(narr[s]);
        return;
    } 
    int mid = s + e >> 1;
    init(x<<1, s, mid); init(x<<1|1, mid+1, e);
    tree[x] = mrg(tree[x<<1], tree[x<<1|1]);
}

void prop(int x, int s, int e){
    if (tree[x].lazy == INF) return;
    tree[x].sum = tree[x].lazy*(e-s+1);
    if (tree[x].lazy <= 0) tree[x].set(0);
    else tree[x].set(tree[x].sum);
    if (s^e) tree[x<<1].lazy = tree[x<<1|1].lazy = tree[x].lazy;
    tree[x].lazy = INF;
}

void update(int x, int s, int e, int l, int r, int w){
    prop(x, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        tree[x].lazy = w;
        prop(x, s, e); return;
    }
    int mid = s + e >> 1;
    update(x<<1, s, mid, l, r, w); update(x<<1|1, mid+1, e, l, r, w);
    tree[x] = mrg(tree[x<<1], tree[x<<1|1]);
}

Node query(int x, int s, int e, int l, int r){
    prop(x, s, e);
    if (e < l || r < s) return Node();
    if (l <= s && e <= r) return tree[x];
    int mid = s + e >> 1;
    Node left = query(x<<1, s, mid, l, r);
    Node right = query(x<<1|1, mid+1, e, l, r);
    return mrg(left, right);
}


void dfs1(int x = 1){
    int msz=0, midx=0;
    for (int i=0; i<g[x].size(); ++i){
        int nxt = g[x][i];
        if (!vst[nxt]){
            vst[nxt] = 1;
            dep[nxt] = dep[x] + 1;
            pr[nxt] = x;
            dfs1(nxt); sz[x] += sz[nxt];
            if (sz[nxt] > msz){
                msz = sz[nxt]; midx = i;
            }
        }
    }
    if (!g[x].empty()) swap(g[x][0], g[x][midx]); 
}

void dfs2(int x = 1){
    in[x] = pv;
    narr[pv++] = arr[x-1];
    for (int i=0; i<g[x].size(); ++i){
        int nxt = g[x][i];
        if (!vst[nxt]){
            vst[nxt] = 1;
            top[nxt] = i? nxt : top[x];
            dfs2(nxt);
        }
    }
}

void query_update(int u, int v, int w){
    while (top[u] ^ top[v]){
        if (dep[top[u]] < dep[top[v]]) swap(u,v);
        int st = top[u];
        update(1,0,n-1,in[st],in[u],w);
        u = pr[st];
    }
    if (dep[u] > dep[v]) swap(u,v);
    update(1,0,n-1,in[u],in[v],w);
}

ll query_ans(int u, int v){
    Node left, right;

    while (top[u] ^ top[v]){
        if (dep[top[u]] > dep[top[v]]){
            left = mrg(query(1, 0, n-1, in[top[u]], in[u]), left);
            u = pr[top[u]];
        } else {
            right = mrg(query(1, 0, n-1, in[top[v]], in[v]), right);
            v = pr[top[v]];
        }   
    }
    if (dep[u] > dep[v]) {
        left = mrg(query(1, 0, n-1, in[v], in[u]), left);
    } else {
        right = mrg(query(1, 0, n-1, in[u], in[v]), right);
    }
    swap(left.lmax, left.rmax);
    left = mrg(left, right);
    return left.max;
}



int main()
{
    fastio
    cin >> n;
    dep.resize(n+1); pr.resize(n+1); in.resize(n+1); top.resize(n+1, 1); sz.resize(n+1, 1);
    g.resize(n+1); vst.resize(n+1); arr.resize(n); narr.resize(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    for (int i=n-1; i--;) {
        int x,y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    vst[1] = 1;
    dfs1();
    vst.assign(n+1,0);
    vst[1] = 1;
    dfs2();
    init(1,0,n-1);
    cin >> m;
    while (m--){
        int q,u,v,w; cin >> q >> u >> v;
        if (q==1){
            cout << query_ans(u,v) << '\n';
        } else{
            cin >> w;
            query_update(u,v,w);
        }
    }


} // namespace std;
