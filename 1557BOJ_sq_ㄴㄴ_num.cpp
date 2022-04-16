#include <bits/stdc++.h>
#define INF 100000000000LL
using namespace std;
using ll = long long;
int k;
vector<int> m(1000000);

ll kth(ll x){
    ll ret = x;
    for (ll i=2; i*i <= x; ++i){
        ret += m[i]*(x/(i*i));
    }
    return x-ret;
}


int main()
{
    cin >> k;
    vector<bool> isprime(1000000,1);
    isprime[0] = isprime[1] = 0;
    for (int i=2; i<1000; ++i) if (isprime[i]) for (int j=i*i; j<1000000; j+=i) isprime[j] = 0;
    vector<int> prime;
    for (int i=2; i<1000000; ++i) if (isprime[i]) prime.push_back(i);

    for (auto p : prime){
        for (ll i=p; i<1000000; i+=p) m[i] += 1;
    }
    for (int i=2; i<1000; ++i) if (m[i]) for (int j=i*i; j<1000000; j+=i*i) m[j] = 0;
    for (int i=2; i<1000000; ++i) if (m[i]) m[i] = m[i]&1? -1:1;
    ll lo = 1, hi = INF;
    while (lo < hi){
        ll mid = lo + hi >> 1;
        ll ret = kth(mid);
        if (ret < k) lo = mid+1;
        else hi = mid;
    }
    cout << lo << '\n';
    // for (int i=0; i<1000; ++i) cout << kth(i) << ' ';
    // cout << endl;

} // namespace std;`
