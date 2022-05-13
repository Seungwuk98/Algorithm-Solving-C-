#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int tree[80808] = {0,};

void update(int i, int z, int s=-10000, int e=10000, int node=1){
    if (s == e) {
        tree[node] += z;
        return;
    }
    int mid = s + e >> 1;
    if (i <= mid) update(i, z, s, mid, node<<1);
    else update(i, z, mid+1, e, node<<1|1);
    tree[node] = tree[node<<1] + tree[node<<1|1];
}

// 게으른 세그먼트 트리 [l r]
// 펜윅 트리
// 머지 소트 트리

int query(int k, int s=-10000, int e=10000, int node=1){
    if (s == e) {
        return s;
    }
    int mid = s + e >> 1;
    int diff = tree[node<<1];
    int ret;
    if (k <= diff) ret = query(k, s, mid, node<<1);
    else ret = query(k-diff, mid+1, e, node<<1|1);
    return ret;
}

int main(){
    fastio
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        update(x,1);
        cout << query(i/2+1) << '\n';
    }
}
// 3, 5, 32, 5124, 123,42,5,12,53,525,235, O(logN)
// 
// BBST ->