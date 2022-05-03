#include <bits/stdc++.h>

using namespace std;


int tree[808080] = {1,};
int arr[101010];
int top, n, m;

void build(int s=1, int e=n+100000, int x=1){
    if (s==e) {
        tree[x] = 1;
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, x<<1);
    build(mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

void update(int i, int s=1, int e=n+100000, int x=1){
    if (s == e) {
        tree[x] = 0;
        return;
    }
    int mid = s + e >> 1;
    if (i <= mid) update(i, s, mid, x<<1);
    else update(i, mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

int query(int l, int r, int s=1, int e=n+100000, int x=1){
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x];
    int mid = s + e >> 1;
    return query(l, r, s, mid, x<<1) + query(l, r, mid+1, e, x<<1|1);
}

int main()
{
    int T; cin >> T;

    while (T--){
        cin >> n >> m;
        top = 100001;
        for (int i=1; i<=n; ++i) arr[i] = i+100000;
        build();
        while (m--){
            int x; cin >> x;
            cout << query(top, arr[x]-1) << '\n';
            update(arr[x]);
            arr[x] = --top;
        }
    }

} // namespace std;
