#include <bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;
    int n,k;
    while (T--) {
        cin >> n >> k;
        vector<int> arr(n);
        for (int i=0; i<n; ++i) cin >> arr[i];
        if (k == 1){
            cout << (n-1>>1) << '\n';
        } else {
            int ans = 0;
            for (int i=1; i<n-1; ++i) if (arr[i] > arr[i-1] + arr[i+1]) ans ++;
            cout << ans << '\n';
        }
    }
}