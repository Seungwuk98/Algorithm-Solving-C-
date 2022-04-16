#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()

using namespace std;
vector<int> fenwick[100001];
int arr[100000];
int n;

void build(){
    for (int i=1; i<=n; ++i){
        for (int j=i-(i&-i); j<i; ++j) fenwick[i].push_back(arr[j]);
        sort(all(fenwick[i]));
    }
}

int query_1_to_r(int r, int k){
    int ret = 0;
    for (; r; r-=r&-r) ret += (r&-r) - (upper_bound(all(fenwick[r]), k) - fenwick[r].begin());
    return ret;
}

int query(int l, int r, int k){
    return query_1_to_r(r, k) - query_1_to_r(l-1, k);
}


int main()
{
    fastio
    cin >> n;
    for (int i=0; i<n; ++i) cin >> arr[i];
    build();
    int m; cin >> m;
    while (m--){
        int i, j, k; cin >> i >> j >> k;
        cout << query(i, j, k) << '\n';
    }
} // namespace std;
