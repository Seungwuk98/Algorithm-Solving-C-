#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

int n, m; 
ll pre[1010101] = {0,};
int mod[1010] = {0,};

int main()
{
    fastio
    cin >> n >> m;
    ll x;
    ll ans = 0;
    for (int i=0; i<n; ++i) {
        cin >> x;
        pre[i+1] = pre[i] + x;
        pre[i+1] %= m; 
        mod[pre[i+1]]++;
    }
    mod[0]++;
    for (int i=0; i<m; ++i) {
        ans += (ll)mod[i]*(mod[i]-1)/2;
    }
    cout << ans;

} // namespace std;
