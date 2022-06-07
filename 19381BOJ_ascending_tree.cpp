#include <bits/stdc++.h>

using namespace std;

int pr[101010];
vector<int> child[101010];
int val[101010];
int n, c;

int dfs(priority_queue<int, vector<int>, greater<int>> &pq, int &ans, int x, int dep=1) {
    pq.pop();
    val[x] += dep;
    int smin = pq.top();
    if (val[x] > smin) ans += val[x] - smin;
    for (int t : child[x]) {
        pq.push(val[x]);
        pq.push(val[x]);
        dfs(pq, ans, t, dep+1);
    }
    pq.pop();

}


int main()
{
    cin >> n >> c;
    val[1] = c;
    for (int i=2; i<=n; ++i) {
        cin >> pr[i] >> val[i];
        child[pr[i]].push_back(i);
    }
    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(val[1]);
    pq.push(val[1]);
    for (auto x : child[1]) dfs(pq, )

} // namespace std;
