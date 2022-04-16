#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = unsigned long long;
using pii = pair<ll,ll>;

int main()
{
    fastio
    stack<pii> s;
    ll result = 0;
    ll n; cin >> n;
    for (ll i=0; i<n; ++i){
        ll x; cin >> x;
        ll j = i;
        while (!s.empty() && s.top().second > x){
            ll h; tie(j,h) = s.top(); s.pop();
            result = max(result, h*(i-j));
        }
        s.push(pii(j,x));
    }
    while (!s.empty()){
            ll j,h; tie(j,h) = s.top(); s.pop();
            result = max(result, h*(n-j));
    }
    cout << result;

} // namespace std;
