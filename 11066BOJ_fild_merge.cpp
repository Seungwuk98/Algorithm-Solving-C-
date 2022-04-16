#include <iostream>
#include <vector>
#define INF 10000000000
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
int main()
{
    fastio
    int T; cin >> T;
    while (T--){
        int n; cin >> n;
        int arr[n];
        for (int i=0; i<n; ++i) cin >> arr[i];
        ll dp[n][n] ={INF,}, c[n][n] = {0};
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) dp[i][j] = INF;
            dp[i][i] = 0;
        } 

        for (int i=0; i<n; ++i) {
            c[i][i] = arr[i];
            for (int j=i+1; j<n; ++j) c[i][j] = c[i][j-1] + arr[j];
        }

        for (int k=1; k<n; ++k){
            for (int i=0; i<n-k; ++i) {
                for (int j=i; j<i+k; ++j) dp[i][i+k] = min(dp[i][i+k], dp[i][j] + dp[j+1][i+k] + c[i][i+k]);
            }
        }
        cout << dp[0][n-1] << endl;

    }
} // namespace 

