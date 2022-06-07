#include <bits/stdc++.h>
#define st first
#define ed second
#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int main()
{
    int n; cin >> n;
    vector<pii> A(n);
    ll time = 1LL<<43;
    for (int i=0; i<n; ++i) {
        cin >> A[i].st >> A[i].ed;
    }
    auto comp = [&](pii &x, pii &y) {
        return x.st > y.st;
    };
    sort(all(A), comp);
    int ans = 0;
    for (int i=0; i<n; ++i) {
        if (time >= A[i].ed){
            time = A[i].st;
            ans ++;
        }
    }
    cout << ans;



} // namespace std;
