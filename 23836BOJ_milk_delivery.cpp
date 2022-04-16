#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using ll = long long;
using namespace std;

struct Node
{
    ll val, lazyA, lazyD;
    Node(){
        val = 0; lazyA = lazyD = 0;
    }
};

Node tree[404040];
int sz[101010], top[101010], dep[101010] = {0,}, in[101010], pr[101010];
bool vst[101010] = {0,};
vector<int> g[101010];
int n, q;

void dfs(int x = 1){
    int msz = -1, idx=0;
    sz[x] = 1;
    for (int i=0; i<g[x].size(); ++i){
        int nxt = g[x][i];
        if (!vst[nxt]){
            vst[nxt] = 1;
            dep[nxt] = dep[x] +1;
            pr[nxt] = x;
            dfs(nxt); sz[x] += sz[nxt];
            if (msz < sz[nxt]) {
                msz = sz[nxt]; idx = i;
            }
        }
    }
    if (!g[x].empty()) swap(g[x][0], g[x][idx]);
}

int pv = 0;
void dfs2(int x = 1){
    in[x] = pv++;
    for (int i=0; i<g[x].size(); ++i){
        int nxt = g[x][i];
        if (!vst[nxt]){
            vst[nxt] = 1;
            top[nxt] = i? nxt : top[x];
            dfs2(nxt);
        }
    }
}

void prop(int x, int s, int e){
    if (!tree[x].lazyA && !tree[x].lazyD) return;
    if (s^e){
        int mid = s + e >> 1;
        tree[x<<1].lazyA += tree[x].lazyA;
        tree[x<<1].lazyD += tree[x].lazyD;
        tree[x<<1|1].lazyA += tree[x].lazyA + (mid+1-s)*tree[x].lazyD;
        tree[x<<1|1].lazyD += tree[x].lazyD;
    } else {
        tree[x].val += tree[x].lazyA;
    }
    tree[x].lazyA = tree[x].lazyD = 0;
}

void update(int A, int D, int l, int r, int s=0, int e=n-1, int x=1){
    prop(x, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        tree[x].lazyA = A + (s-l)*D;
        tree[x].lazyD = D;
        prop(x, s, e);
        return;
    }
    int mid = s + e >> 1;
    update(A, D, l, r, s, mid, x<<1); update(A, D, l, r, mid+1, e, x<<1|1);
}

ll query(int v, int s=0, int e=n-1, int x=1){
    prop(x, s, e);
    if (s == e) return tree[x].val;
    int mid = s + e >> 1;
    if (v <= mid) return query(v, s, mid, x<<1);
    return query(v, mid+1, e, x<<1|1);
}

int lca(int u, int v){
    while (top[u] != top[v]){
        if (dep[top[u]] < dep[top[v]]) swap(u,v);
        u = pr[top[u]];
    }
    if (dep[u] > dep[v]) swap(u,v);
    return u;
}

void update(int u, int v){
    int w = lca(u,v);
    int dist = dep[u] + dep[v] - 2*dep[w];
    int A = 0;
    while (top[u] != top[w]){
        int st = top[u];
        A += in[u] - in[st];
        update(A,-1,in[st],in[u]);
        u = pr[st];
        A++;
    }
    int B = dist;
    while (top[v] != top[w]){
        int st = top[v];
        B -= in[v] - in[st];
        update(B,1,in[st],in[v]);
        v = pr[st];
        B--;
    }
    if (u == w){
        B -= in[v] - in[u];
        update(B,1,in[u],in[v]);
    } else {
        A += in[u] - in[v];
        update(A,-1,in[v],in[u]);
    }
}

int main()
{
    fastio
    cin >> n; top[1] = 1; vst[1] = 1;
    for (int i=0; i<n-1; ++i){
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs();
    fill(&vst[0], &vst[n+1], 0);
    vst[1] = 1;
    dfs2();
    cin >> q;
    while (q--){
        int op, u, v;
        cin >> op;
        if (op == 1){
            cin >> u >> v;
            update(u, v);
        } else {
            cin >> u;
            cout << query(in[u]) << '\n';
        }
    }

} // namespace std;
