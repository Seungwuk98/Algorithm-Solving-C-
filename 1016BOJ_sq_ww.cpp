#include <bits/stdc++.h>

using namespace std;
using ll = long long;
vector<int> m(1001001,1);

ll kth(ll x){
    ll ret = x;
    for (ll i=2; i*i<=x; ++i) if (m[i]) ret -= x/(i*i)*m[i];
    return ret;
}

int main()
{
    m[0]=m[1]=0;
    for (int i=2; i<=1001000; ++i) if (m[i]) for (int j=i*2; j<=1001000; j+=i) m[j] -= m[i];
    ll mn, mx; cin >> mn >> mx;
    cout << kth(mx) - kth(mn-1);    

} // namespace std;
