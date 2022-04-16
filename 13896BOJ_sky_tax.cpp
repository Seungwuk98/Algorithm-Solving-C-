#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#define all(v) v.begin(), v.end()
#define LOG 18

using namespace std;
vector<vector<int>> g, pr;
vector<int> sz, in, out, dep;
vector<bool> vst;
int pv = 0;

void dfs(int node = 1){
    in[node] = pv++;
    for (int &next : g[node]){
        if (!vst[next]){
            vst[next] = 1;
            dep[next] = dep[node]+1;
            pr[next][0] = node;
            dfs(next); sz[node] += sz[next];
        }
    }
    out[node] = pv;
}

void parent(int n){
    for (int i=1; i<LOG; ++i)
        for (int j=1; j<=n; ++j)
            pr[j][i] = pr[pr[j][i-1]][i-1];
}

int get_parent(int node, int k){
    for (int i=LOG-1; i>=0; --i){
        if (k >= (1<<i)) {
            node = pr[node][i];
            k -= 1<<i;
        }
    }
    return node;
}

int get_lca(int a, int b){
    if (dep[a] < dep[b]) swap(a,b);
    for (int i=LOG-1; i>=0; --i) if (dep[a]-dep[b] >= (1<<i)) a = pr[a][i];
    if (a == b) return a;
    for (int i=LOG-1; i>=0; --i) if (pr[a][i] != pr[b][i]) {
        a = pr[a][i]; b = pr[b][i];
    }
    return pr[a][0];
}

bool is_child(int p, int c){
    return in[p] <= in[c] && in[c] < out[p];
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for (int z=1; z<=T; ++z) {
        cout << "Case #" << z << ":\n";
        int n,q,r; cin >> n >> q >> r;
        g.clear(); g.resize(n+1);
        sz.clear(); sz.resize(n+1,1);
        dep.clear(); dep.resize(n+1);
        in.clear(); in.resize(n+1);
        out.clear(); out.resize(n+1);
        vst.clear(); vst.resize(n+1);
        pr.clear(); pr.resize(n+1);
        for (int i=0; i<n+1; ++i) pr[i].resize(LOG);
        for (int i=n-1; i--;){
            int x,y; cin >> x >> y;
            g[x].push_back(y); g[y].push_back(x);
        }
        vst[1] = 1;
        dfs(); parent(n);
        while (q--){
            int s, u; cin >> s >> u;
            if (s){
                if (u == r) cout << n << '\n';
                else if (is_child(r, u)) cout << sz[u] << '\n';
                else {
                    int lca = get_lca(u, r);
                    int ret;
                    if (lca == u) {
                        int cd = get_parent(r, dep[r]-dep[lca]-1);
                        ret = n - sz[cd];
                    } else {
                        ret = sz[u];
                    }
                    cout << ret << '\n';
                }
            } else {
                r = u;
            }
        }
    }
    
} // namespace std;
