#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
using namespace std;
using pii = pair<int, int>;
int v, e;
int pr[50505];
int rk[50505] = {0,};
int in[50505] = {0,}, top[50505], dep[50505] = {0,}, sz[50505];
int arr[50505];
vector<pii> g[50505];


int find(int x) {
    return pr[x] == x ? x : (pr[x] = find(pr[x]));
}

bool uni(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    if (rk[rx] > rk[ry]) pr[ry] = rx;
    else {
        pr[rx] = ry;
        if (rk[rx] == rk[ry]) rk[ry]++;
    }
    return true;
}

void dfs1(int p=0, int x=1) {
    int msz = -1, id = 0;
    sz[x] = 1;
    for (int i=0; i<g[x].size(); ++i) {
        auto [nxt, c] = g[x][i];
        if (p != nxt) {
            dep[nxt] = dep[x] + 1;
            pr[nxt] = x;
            dfs1(x, nxt);
            if (sz[x] > msz) {
                msz = sz[x]; id = i;
            }
        }
    }
    if (!g[x].empty()) swap(g[x][id], g[x][0]);
}

int pv = 0;
void dfs2(int p=0, int x=1, int cs=0) {
    in[x] = pv;
    arr[pv++] = cs;
    for (int i=0; i<g[x].size(); ++i) {
        auto [nxt, c] = g[x][i];
        if (p != nxt) {
            top[nxt] = i ? top[x] : x;
            dfs2(x, nxt, c);
        }
    }
}

struct Segtree
{
    int mx[1<<17] = {0,};
    const int HF = 1<<16;
    void build(int *arr, int sz) {
        for (int i=0; i<sz; ++i) mx[i|HF] = arr[i];
        for (int i=HF-1; i>0; --i) mx[i] = max(mx[i<<1], mx[i<<1|1]);
    }

    int query(int l, int r) {
        int ret = 0;
        for (l|=HF, r|=HF; l<=r; l>>=1, r>>=1) {
            if (l&1) ret = max(ret, mx[l++]);
            if (~r&1) ret = max(ret, mx[r--]);
        }
        return ret;
    }
} tree;

int query(int u, int v) {
    int ret = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        ret = max(ret, tree.query(in[st], in[u]));
        u = pr[st];
    }
    if (u == v) return ret;
    if (dep[u] > dep[v]) swap(u, v);
    return max(ret, tree.query(in[u]+1, in[v]));
}

using piii = tuple<int, int, int>;

int main()
{
    fastio
    cin >> v >> e;
    for (int i=1; i<=v; ++i) pr[i] = i;
    int u, v, c;
    vector<piii> edge;
    for (int i=0; i<e; ++i) {
        cin >> u >> v >> c;
        edge.push_back({c, u, v});
    }
    sort(all(edge));
    int ret = 0;
    unordered_set<int> S;
    for (int i=0; i<e; ++i) {
        auto [c, u, v] = edge[i];
        if (uni(u, v)) {
            ret += c;
            g[u].push_back({v, c});
            g[v].push_back({u, c});
        } else {
            S.insert(i);
        }
    }

    top[1] = 1;
    // cout << 1 << endl;
    // dfs1();
    // dfs2();
    // tree.build(arr, v);
    // int ans = 2147483647;
    // for (int i : S) {
    //     auto [c, u, v] = edge[i];
    //     int pmx = query(u, v);
    //     if (c == pmx) continue;
    //     ans = min(ans, ret - pmx + c);
    // }
    // cout << ans;
} // namespace std;
