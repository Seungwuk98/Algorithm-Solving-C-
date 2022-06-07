#include <bits/stdc++.h>

using namespace std;

int dp[1010][1010] = {0,};
int A[1010];
int B[1010];
int n;

int main()
{
    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> A[i];
        B[i] = A[i];
    } 
    sort(B, B+n);
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            if (A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }
    }

    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=n; ++j) cout << dp[i][j] << ' ';
        cout << endl;
    }
    cout << dp[n][n];

} // namespace std

