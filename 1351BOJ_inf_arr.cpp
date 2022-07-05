#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()

using namespace std;

int dp[10000001];
bool chk[10000001] = {0,};

int main()
{
    int n; cin >> n;
    for (int i=10000000; i>0; --i) {
        vector<int> ni;
        for (int x=i; x; x/=10) ni.push_back(x%10);
        if (ni[0] > ni.back()) continue;
        reverse(all(ni));
        int r = 0;
        for (int i=0, c=1; i<ni.size(); ++i, c*=10) r += ni[i]*c;
        if (i>=r) {
            dp[i-r] = i;
            chk[i-r] = 1;
        } 
    }
    cout << (chk[n] ? dp[n] : -1);

} // namespace std;

