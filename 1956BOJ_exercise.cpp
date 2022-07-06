#include <bits/stdc++.h>

using namespace std;

int v, e;

int d[404][404];

int main()
{
    cin >> v >> e;
    fill(&d[0][0], &d[v][v+1], 1<<29);
    for (int i=0; i<e; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = c;
    }
    for (int k=1; k<=v; ++k) for (int i=1; i<=v; ++i) for (int j=1; j<=v; ++j) d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
    int ans = 1<<29;
    for (int i=1; i<=v; ++i) ans = min(ans, d[i][i]);
    cout << (ans == 1<<29 ? -1 : ans);

} // namespace std;
