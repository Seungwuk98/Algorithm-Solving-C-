#include <bits/stdc++.h>

using namespace std;
int main()
{
    vector<int> arr;
    int n,m; cin >> n >> m;
    int ret = 0;
    int mn = 100000;
    for (int i=1; i*i<=10000; ++i){
        if (n <= i*i && i*i <= m) {
            ret += i*i;
            mn = min(mn, i*i);
        } 
    }
    if (mn == 100000) cout << -1;
    else cout << ret << '\n' << mn;
    
} // namespace std;
