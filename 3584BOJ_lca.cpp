#include <bits/stdc++.h>

using namespace std;


int main()
{
    int T; cin >> T;
    while (T--){
        int n; cin >> n;
        vector<int> pr(n+1);
        for (int i=n-1; i--;) {
            int x, y; cin >> x >> y;
            pr[y] = x;
        }
        vector<bool> vst(n+1);
        int u,v; cin >> u >> v;
        
        while (u){
            vst[u] = 1;
            u = pr[u];
        }

        while (!vst[v]) v = pr[v];
        cout << v << '\n';
    }
} // namespace std;
