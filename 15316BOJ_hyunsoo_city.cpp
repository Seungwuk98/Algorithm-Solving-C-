#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
pii Edge[202020];

map<pii, int> M;
vector<pii> Q;
int n, m, t = 0;

vector<pii> tree[808080];

void update(pii ed, int l, int r, int s=0, int e=t-1, int x=1) {
    if (e < l || r < s) return ;
    if (l <= s && e <= r) {
        tree[x].push_back(ed);
        return;
    }
    int mid = s + e >> 1;
    update(ed, l, r, s, mid, x<<1); update(ed, l, r, mid+1, e, x<<1|1);
}

int pr[202020];
int rk[202020] = {0,};

int find(int x){
    return pr[x] == x ? x : find(pr[x]);
}

piii uni(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return {0, 0, 0};
    if (rk[rx] < rk[ry]) {
        pr[rx] = ry;
        return {rx, ry, 0};
    } 
    else if (rk[ry] < rk[rx]) {
        pr[ry] = rx;
        return {ry, rx, 0};
    }
    pr[rx] = ry;
    rk[ry]++;
    return {rx, ry, 1};
}

void sep(int c, int p, int t) {
    pr[c] = c;
    rk[p] -= t;
}

void solve(int l = 0, int r = t-1, int x=1) {
    vector<piii> mem;
    for (auto [u, v] : tree[x]) {
        mem.push_back(uni(u, v));
    }
    if (l == r) {
        auto [u, v] = Q[l];
        cout << (find(u) == find(v) ? "YES" : "NO") << ' ';
    } else {
        int mid = l + r >> 1;
        solve(l, mid, x<<1);
        solve(mid+1, r, x<<1|1);
    }
    while (!mem.empty()) {
        auto [c, p, t] = mem.back(); mem.pop_back();
        sep(c, p, t);
    }
}

int main()
{
    fastio
    cin >> n >> m;
    for (int i=1; i<=n; ++i) pr[i] = i;
    
    int a, b;
    for (int i=1; i<=m; ++i) {
        cin >> a >> b;
        Edge[i] = {a, b};
    }
    for (int i=1; i<=m; ++i) {
        bool c; cin >> c;
        if (c) {
            M[Edge[i]] = t;
        }
    }

    vector<pair<pii,pii>> time;
    int q; cin >> q;
    int op, x, y, z;
    while (q--){
        cin >> op >> x;
        if (op == 1) {
            if (M.find(Edge[x]) == M.end()) {
                M[Edge[x]] = t;
            } else {
                int l = M[Edge[x]];
                M.erase(Edge[x]);
                int r = t-1;
                if (l <= r) {
                    time.push_back({Edge[x], {l, r}});
                }
            }
        } else {
            cin >> y;
            Q.push_back({x, y});
            t++;
        }
    }


    for (auto [x, y] : time) {
        update(x, y.first, y.second);
    }

    for (auto [k, l] : M) {
        update(k, l, t-1);        
    }

    solve();
} // namespace std;
