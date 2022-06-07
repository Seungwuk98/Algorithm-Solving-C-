#include <bits/stdc++.h>

using namespace std;

int dp[1010][1010] = {0,};
int main()
{
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }   
    }
    cout << dp[n][m];
} // namespace std;
