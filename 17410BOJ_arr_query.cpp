#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <set>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()

using namespace std;


int main()
{
    fastio
    int n,m; cin >> n;
    int sn = int(sqrt(n))+1;
    vector<int> arr(n);
    vector<vector<int>> tree(sn);
    for (int i=0; i<n; ++i){
        cin >> arr[i];
        tree[i/sn].push_back(arr[i]);
    }
    for (int i=0; i<sn; ++i) sort(all(tree[i]));
    cin >> m;
    while (m--){
        int q,i,j,k; cin >> q;
        if (q==1){
            cin >> i >> k;
            i--;
            int idx = lower_bound(all(tree[i/sn]), arr[i]) - tree[i/sn].begin();

            arr[i] = k;
        } else{
            cin >> i >> j >> k;
            i--; j--;
            int ret = 0;
            if (i/sn == j/sn){
                for (register int x=i; x<=j; ++x) if (arr[x] > k) ret++;
            } else {
                int l = min(i/sn*sn+sn, n);
                for (register int x=i; x<l; ++x) if (arr[x] > k) ret++;
                for (register int x=j/sn*sn; x<=j; ++x) if (arr[x] > k) ret++;
                for (register int x=i/sn+1; x<j/sn; ++x) ret += trees[x].query(k+1, 10000);
            }
            cout << ret << '\n';
        }
    }


} // namespace std;
