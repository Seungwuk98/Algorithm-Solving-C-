#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<int> dep;
vector<bool> vst;
int n;

void dfs(int node = 1){
    for (int x : g[node]){
        if (vst[x]) continue;
        vst[x] = 1;
        dep[x] = dep[node]+1;
        dfs(x);
    }
}

int main()
{
    cin >> n;
    g.resize(n+1);
    dep.resize(n+1);
    vst.resize(n+1,false);
    for (int i=n-1; i--;){
        int a,b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int now = 0;
    int prev; cin >> prev;
    vst[prev] = 1;
    dfs(prev);
    for (int i=n-1;i--;){
        int node; cin >> node;
        if (dep[prev]!= dep[node]) now++;
        if (dep[node]!=now){
            cout << 0;
            return 0;
        }
        prev = node;
    }
    cout << 1;


} // namespace std;
