#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int n, m;
int arr[2000];
bool dp[2000][2000] = {0,};

int main(){
    fastio
    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
        dp[i][i] = 1;
        if (i) dp[i-1][i] = arr[i] == arr[i-1];
    } 

    for (int j=2; j<n; ++j) for (int i=0; i<n-j; ++i) 
        if (arr[i] == arr[i+j]) dp[i][i+j] = dp[i+1][i+j-1];

    cin >> m;
    int x,y;
    while (m--) {
        cin >> x >> y;
        cout << dp[x-1][y-1] << '\n';
    }

}