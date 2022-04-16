#include <bits/stdc++.h>
#define INF 1000000000000LL;

using namespace std;
using ll = long long;
vector<int> m(1000001,1);
ll k;

ll kth(ll x){
    ll ret = 0;
    for (ll i=2; i*i<=x; ++i){
        if (m[i]) ret += m[i]*(x/(i*i));
    }
    return ret;
}

int main()
{
    cin >> k;
    m[0] = m[1] = 0;
    for (int i=2; i<1000001; ++i) if (m[i]) for (int j=i*2; j<1000001; j+=i) m[j] -= m[i];

    ll lo = 4, hi = INF;
    while (lo < hi){
        ll mid = lo + hi >> 1;
        ll ret = kth(mid);
        if (ret < k) lo = mid+1;
        else hi = mid;
    }
    cout << lo;
} // namespace std;
