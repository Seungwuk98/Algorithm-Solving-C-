#include <iostream>
#include <math.h>

using namespace std;
using ll = long long;
int main()
{
    ll n; cin >> n;
    ll mpf[n+1];
    for (ll i=0; i<=n; ++i) mpf[i] = i;
    ll sn = int(sqrt(n));
    for (ll i=2; i<=sn; ++i){
        if (mpf[i] == i){
            for (ll j=i*i; j<=n; j+=i){
                if (mpf[j] == j) mpf[j] = i;
            }
        }
    }

    while (n!=1){
        cout << mpf[n] << '\n';
        n/=mpf[n];
    }
} // namespace std;
