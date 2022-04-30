#include <bits/stdc++.h>

using namespace std;

vector<int> g[101];
bool vst[101]={0,};
int main()
{
    int n, s, e, m; cin >> n >> s >> e >> m;
    for (int i=0; i<n; ++i) {
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    queue<int> q;
    q.push(s);
    vst[s] = 1;
    int count = -1;
    while (!q.empty()) {
        int l = q.size();
        count++;
        while (l--){
            int now = q.front(); q.pop();
            if (now == e) {
                cout << count;
                return 0;
            }
            for (int i=0; i<g[now].size(); ++i) {
                int nxt = g[now][i];
                if (vst[nxt]) continue;
                vst[nxt] = 1;
                q.push(nxt);
            }
        }        
    }
    cout << -1;
} // namespace std;
