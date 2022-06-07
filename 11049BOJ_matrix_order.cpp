#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll dp[500][500];
int sz[500][2];
const ll INF = 1LL<<60;

int main(){
    int n; cin >> n;
    fill(&dp[0][0], &dp[n-1][n], INF);
    for (int i=0; i<n; ++i) {
        cin >> sz[i][0] >> sz[i][1];
        dp[i][i] = 0;
    } 
    for (int i=1; i<n; ++i) {
        for (int j=0; j<n-i; ++j) {
            int k = j+i, p1, p2, p3;
            p1 = sz[j][0], p2 = sz[k][1];
            for (int l=j; l<k; ++l) {
                p3 = sz[l][1];
                dp[j][k] = min(dp[j][k], dp[j][l] + dp[l+1][k] + (ll)p1*p2*p3);
            }
        }
    }

    cout << dp[0][n-1];
}