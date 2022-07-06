#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF 2'000'000'234
#define all(v) v.begin(), v.end()
using namespace std;
using piii = tuple<int, int, int>;

int main()
{
    fastio
    int n; cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    piii ans = {INF, INF, INF};

    sort(all(arr));
    for (int i=0, j=n-1; i<j; ) {
        int X = arr[i] + arr[j];
        piii p = {abs(X), arr[i], arr[j]};
        ans = min(ans, p);
        if (X > 0) j--;
        else if (X < 0) i++;
        else break;
    }
    auto [x, y, z] = ans;
    cout << y << ' ' << z;
} // namespace std;
