#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;
vector<int> top, sz, dep, pr;
vector<bool> vst;
vector<vector<int>> g;
int n,m;

void dfs1(int node=1){
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

void dfs2(int node=1){
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        top[next] = i? next : top[node];
        dfs2(next);
    }
}

int query(int u, int v){
    while (top[u] != top[v]){
        if (dep[top[u]] < dep[top[v]]) swap(u,v);
        u = pr[top[u]];
    }
    if (dep[u] > dep[v]) swap(u,v);
    return u;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    top.resize(n+1,1); sz.resize(n+1,1); dep.resize(n+1); pr.resize(n+1);
    g.resize(n+1); vst.resize(n+1);
    for (int i=n-1; i--;){
        int x,y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    vst[1] = 1;
    dfs1();
    fill(vst.begin(), vst.end(), 0);
    vst[1] = 1;
    dfs2();
    cin >> m;
    while (m--){
        int x, y; cin >> x >> y;
        cout << query(x,y) << '\n';
    }

}
