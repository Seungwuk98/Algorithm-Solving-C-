#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

int A[1010101];
int ans[1010101];
int main()
{
    fastio   
    int n;
    cin >> n;
    for (int i=0; i<n; ++i) cin >> A[i];

    priority_queue<int, vector<int>, less<int>> pq;
    pq.push(A[0]);
    pq.push(A[0]);
    ans[0] = A[0];

    for (int i=1; i<n; ++i) {
        pq.pop();
        A[i] -= i;
        int smax = pq.top();
        ans[i] = max(smax, A[i]) + i;
        pq.push(A[i]);
        pq.push(A[i]);
    }
    for (int i=n-2; i>=0; --i) ans[i] = min(ans[i], ans[i+1]-1);
    for (int i=0; i<n; ++i) cout << ans[i] << ' ';


} // namespace std;
