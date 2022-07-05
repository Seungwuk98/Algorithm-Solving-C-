#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastio
    int T; cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i=0; i<n; ++i) cin >> arr[i];

        int ans = 0;
        int t, l;
        for (int i=0; i<n; ++i) {
            t = arr[i];
            l = 0;
            for (int j=0; j<n; ++j) {
                if (i!=j) l ^= arr[j];
            }
            if (t == l) {
                ans = t;
                break;
            }
        }
        cout << ans << endl;

    }
} // namespace std;
