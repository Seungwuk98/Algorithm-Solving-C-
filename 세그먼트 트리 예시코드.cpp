#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define all(v) v.begin(), v.end()

using namespace std;

vector<int> tree[404040];
int arr[101010];
int n, m;

void merge(vector<int> &ans, vector<int> &left, vector<int> &right){
    ans.resize(left.size() + right.size());
    int i, j, k; i = j = k;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) ans[k++] = left[i];
        else ans[k++] = right[j];
    }
    while (i < left.size()) ans[k++] = left[i++];
    while (j < right.size()) ans[k++] = right[j++];
}


void build(int start=1, int end=n, int node=1) {
    if (start == end) {
        tree[node].push_back(arr[start]);
        return;
    }
    int mid = start + end >> 1;
    build(start, mid, node<<1);
    build(mid+1, end, node<<1|1);
    merge(tree[node], tree[node<<1], tree[node<<1|1]);
}

int query(int k, int l, int r, int start=1, int end=n, int node=1){
    if (end < l || r < start) return 0;
    if (l <= start && end <= r) {
        // k보다 큰 원소의 개수. 구간의 개수 - k이하 값의 개수
        return (end - start + 1) - 
            (upper_bound(all(tree[node]), k) - tree[node].begin());
    }
    int mid = start + end >> 1;
    return query(k, l, r, start, mid, node<<1) +
            query(k, l, r, mid+1, end, node<<1|1);
}

int main()
{
    fastio
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> arr[i];
    build();
    cin >> m;
    int i,j,k;
    while (m--) {
        cin >> i >> j >> k;
        cout << query(k, i, j) << '\n';
    }

} // namespace std;
