#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
using namespace std;
using piii = tuple<int, int, int>;
const int INF = 1000'000'000;


int dp[101][10001] = {0,};
vector<piii> g[101];
int main()
{
    fastio
    int T; cin >> T;
    while (T--){
        int n,m,k;
        cin >> n >> m >> k;
        for (int i=1; i<=n; ++i) for (int j=0; j<=m; ++j) dp[i][j] = INF;
        for (int i=1; i<=n; ++i) g[i].clear();

        while (k--){
            int u,v,c,d;
            cin >> u >> v >> c >> d;
            g[u].push_back({d,c,v});
        }

        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({0,0,1});
        while (!pq.empty()) {
            int dist, cost, now;
            tie(dist, cost, now) = pq.top(); pq.pop();
            if (dp[now][cost] < dist) continue;

            for (int i=0; i<g[now].size(); ++i){
                int next_dist, next_cost, next;
                tie(next_dist, next_cost, next) = g[now][i];
                int from_dist = next_dist + dist;
                int from_cost = next_cost + cost;
                if (from_cost <= m && dp[next][from_cost] > from_dist) {
                    for (int j=from_cost; j<=m; ++j) {
                        if (dp[next][j] <= from_dist) break;
                        dp[next][j] = from_dist;
                    }
                    pq.push({from_dist, from_cost, next});
                }
            }
        }
        int ret = INF;
        for (int i=0; i<=m; ++i) ret = min(ret, dp[n][i]);
        if (ret == INF) cout << "Poor KCM" << '\n';
        else cout << ret << '\n';

    }
} // namespace std;
