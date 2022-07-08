#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T; cin >> T;



    while (T--) {
        int n; cin >> n;
        if (n&1) cout << -1 << '\n';
        else cout << "0 0 " << (n>>1) << '\n';
    }
} // namespace std;
