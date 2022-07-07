#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int n, k, arr[101010], pre[101010] = {0,};

int main()
{
    fastio
    cin >> n >> k;
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
        pre[i+1] = pre[i] + arr[i];
    } 
    int ans = 1<<31;
    for (int i=0; i<=n-k; ++i) ans = max(ans, pre[i+k]-pre[i]);
    cout << ans;

} // namespace std;
