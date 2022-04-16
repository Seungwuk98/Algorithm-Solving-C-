#include <iostream>
#include <vector>
#define INF 1000000000000000LLU
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = unsigned long long;

ll dp[5000][5000];
int c[5001], opt[5000][5000];

int main()
{
    fastio
    int T; cin >> T;
    while (T--){
        int n; cin >> n;
        fill(&dp[0][0], &dp[n-1][n], INF);
        c[0] = 0;
        for (int i=0; i<n; ++i) {
            dp[i][i] = 0;
            opt[i][i] = i;
            int x; cin >> x;
            c[i+1] = c[i] + x;
        }
        for (int k=1; k<n; ++k){
            for (int i=0; i<n-k; ++i){
                for (int j=opt[i][i+k-1]; j<=opt[i+1][i+k] && j<n-1; ++j){
                    ll tmp = dp[i][j] + dp[j+1][i+k] + c[i+k+1] - c[i];
                    if (dp[i][i+k] > tmp){
                        opt[i][i+k] = j; dp[i][i+k] = tmp;
                    }
                }
            }
        }
        cout << dp[0][n-1] << '\n';

    }

} // namespace std;
