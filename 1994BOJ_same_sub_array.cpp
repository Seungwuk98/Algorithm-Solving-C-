#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll A[2020];

int main()
{
    int n; cin >> n;
    for (int i=0; i<n; ++i) cin >> A[i];
    sort(A, A+n);
    n = unique(A, A+n) - A;
    for (int i=1; i<n-1; ++i) A[i] = A[i]*2 - A[i-1] - A[i+1];
    int ret = min(2, n);
    int now = 0;
    for (int i=1; i<n-1; ++i) {
        if (A[i] == 0) now++, ret = max(ret, now+2);
        else now = 0;
    }
    cout << ret;


} // namespace std;
