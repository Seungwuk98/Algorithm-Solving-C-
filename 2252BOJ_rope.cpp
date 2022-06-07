#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g[32323];
bool vst[32323] = {0,};
int n,m;

void dfs(int v) {
    vst[v] = 1;
    for (int nxt : g[v]) if (!vst[nxt]) dfs(nxt);
    cout << v << ' ';
}

int main(){
    cin >> n >> m;
    while (m--) {
        int a,b; cin >> a >> b;
        g[b].push_back(a);
    }   
    for (int i=1; i<=n; ++i) if (!vst[i]) dfs(i);
}