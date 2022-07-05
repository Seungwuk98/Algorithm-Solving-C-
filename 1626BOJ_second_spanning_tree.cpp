#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ll = long long;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int v, e;
int pr[50505][16], dep[50505] = {0,}, mx[50505][16], smx[50505][16], rk[50505] = {0,};
vector<pii> g[50505];


int find(int x) {
    return pr[x][0] == x ? x : (pr[x][0] = find(pr[x][0]));
}

bool uni(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    if (rk[rx] < rk[ry]) pr[rx][0] = ry;
    else {
        pr[ry][0] = rx;
        if (rk[rx] == rk[ry]) rk[rx]++;
    }
    return true;
}


void dfs(int p=-1, int x=1) {
    for (auto [nxt, c] : g[x]) if (nxt != p) {
        pr[nxt][0] = x;
        dep[nxt] = dep[x] + 1;
        mx[nxt][0] = c;
        dfs(x, nxt);
    }
}

pii find_mx_smx(int mx1, int mx2, int smx1, int smx2) {
    int ret_mx = -1, ret_smx = -1;
    if (mx1 == mx2) {
        ret_mx = mx1;
        ret_smx = max(smx1, smx2);
    } else if (mx1 > mx2) {
        ret_mx = mx1;
        ret_smx = max(mx2, smx1);
    } else {
        ret_mx = mx2;
        ret_smx = max(mx1, smx2);
    }
    return {ret_mx, ret_smx};
}


void buildpr() {
    for (int i=1; i<16; ++i) for (int j=1; j<=v; ++j) {
        pr[j][i] = pr[pr[j][i-1]][i-1];
        tie(mx[j][i], smx[j][i]) = find_mx_smx(mx[j][i-1], mx[pr[j][i-1]][i-1], smx[j][i-1], smx[pr[j][i-1]][i-1]);
    }
}

pii query(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int ret_mx = -1;
    int ret_smx = -1;
    for (int i=15; i>=0; --i) if ((dep[v] - dep[u]) & (1<<i)) {
        tie(ret_mx, ret_smx) = find_mx_smx(ret_mx, mx[v][i], ret_smx, smx[v][i]);
        v = pr[v][i];
    } 
    if (u == v) return {ret_mx, ret_smx};
    for (int i=15; i>=0; --i) if (pr[u][i] != pr[v][i]) {
        tie(ret_mx, ret_smx) = find_mx_smx(ret_mx, mx[v][i], ret_smx, smx[v][i]);
        tie(ret_mx, ret_smx) = find_mx_smx(ret_mx, mx[u][i], ret_smx, smx[u][i]);
        u = pr[u][i]; v = pr[v][i];
    }
    tie(ret_mx, ret_smx) = find_mx_smx(ret_mx, mx[v][0], ret_smx, smx[v][0]);
    tie(ret_mx, ret_smx) = find_mx_smx(ret_mx, mx[u][0], ret_smx, smx[u][0]);
    return {ret_mx, ret_smx};
}

int main()
{
    fastio
    cin >> v >> e;
    for (int i=1; i<=v; ++i) pr[i][0] = i;
    vector<piii> edges;
    while (e--) {
        int x, y, z;
        cin >> x >> y >> z;
        edges.push_back({z, x, y});
    }
    sort(all(edges));
    ll mst = 0;
    vector<piii> S;
    for (auto [c, x, y] : edges) {
        if (uni(x, y)) {
            g[x].push_back({y, c});
            g[y].push_back({x, c});
            mst += c;
        } else {
            S.push_back({c,x,y});
        }
    }
    int r = find(1);
    for (int i=2; i<=v; ++i) if(find(i) != r) {
        cout << -1; return 0;
    }
    fill(&smx[0][0], &smx[v][16], -1);
    fill(&mx[0][0], &mx[v][16], -1);
    dfs();
    buildpr();
    ll ans = 1LL<<62;
    for (auto [c, x, y] : S) {
        auto [ret_mx, ret_smx] = query(x, y);
        if (ret_mx != c && ret_mx != -1) ans = min(ans, mst - ret_mx + c);
        if (ret_smx != c && ret_smx != -1) ans = min(ans, mst - ret_smx + c);
    }
    cout << (ans == 1LL<<62 ? -1 : ans);


} // namespace std;

