#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define INF 1000000000LLU
using namespace std;
using ll = unsigned long long;

int n;

tuple<ll, ll> count(ll x){
    ll und=0, bel=0;
    for (int i=1; i<=n; ++i){
        if (x > n*i) {
            bel += n; und += n; continue;
        }
        ll z = x/i;
        bel += z;
        und += (x%i)? z : z-1;
    }
    return make_tuple(und, bel);
}

ll bi(int k){
    ll lo = 0, hi = INF;
    while (lo < hi){
        ll mid = lo + hi >> 1;
        ll und, bel;
        tie(und, bel) = count(mid);
        if (bel < k) lo = mid + 1;
        else if (und >= k) hi = mid - 1;
        else return mid;
    }
    return lo;
}

int main()
{
    cin >> n; int k; cin >> k;
    cout << bi(k) << '\n';

} // namespace stdl
