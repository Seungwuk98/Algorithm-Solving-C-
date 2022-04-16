#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define INF 1000000
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


using namespace std;
using pii = pair<int,int>;

int n,m;
int s,e;
int result = 0;
vector<vector<pii>> g;

void dfs(int v, int pr, int cst){
    cout << v << ' ' << pr << endl;
    if (v == e) {
        result = max(cst, result);
        return;
    }
    for (auto &p : g[v]) if (p.first != pr) {
        int nxt, w;

        tie(nxt,w) = p;
        int fs = min(cst, w);
        if (fs > result) dfs(nxt, v, fs);
    }
}


int main()
{
    cin >> n >> m >> s >> e;
    g.resize(n+1);
    while (m--){
        int x, y, w;
        cin >> x >> y >> w;
        g[x].push_back(pii(y,w)); g[y].push_back(pii(x,w));
    }
    dfs(s,0,INF);
    cout << 1 << endl;
    cout << result;
} // namespace std;
