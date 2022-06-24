#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
pii Edge[101010];

map<pii, int> M;
vector<pii> Q;
int n, m, t = 0;

vector<pii> tree[404040];

void update(pii ed, int l, int r, int s=0, int e=t-1, int x=1) {
    if (e < l || r < s) return ;
    if (l <= s && e <= r) {
        tree[x].push_back(ed);
        return;
    }
    int mid = s + e >> 1;
    update(ed, l, r, s, mid, x<<1); update(ed, l, r, mid+1, e, x<<1|1);
}

int pr[101010];
int rk[101010] = {0,};

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
        cout << (find(u) == find(v)) << ' ';
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
    
    int op, a, b;
    vector<pair<pii,pii>> time;
    while (m--) {
        cin >> op >> a >> b;
        if (a > b) swap(a, b);
        if (op == 1) {
            M[{a,b}] = t;
        } else if (op == 2){
            int l = M[{a,b}];
            M.erase({a,b});
            int r = t-1;
            if (l <= r) {
                time.push_back({{a,b},{l,r}});
            }
        } else {
            Q.push_back({a,b});
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
