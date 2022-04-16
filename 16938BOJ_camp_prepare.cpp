#include <bits/stdc++.h>

using namespace std;
int main()
{
    int n,l,r,x; cin >> n >> l >> r >> x;
    vector<int> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];

    int ret = 0;
    for (int i=1; i<(1<<n); ++i){
        int sm, mx, mn; 
        sm = mx = 0; mn = 1<<30;
        for (int j=0; j<n; ++j) if (i>>j&1){
            sm += arr[j];
            mx = max(mx, arr[j]);
            mn = min(mn, arr[j]);
        }
        if (l<=sm && sm<=r && mx-mn>=x) ret++; 
    }
    cout << ret;

} // namespace sdt;
