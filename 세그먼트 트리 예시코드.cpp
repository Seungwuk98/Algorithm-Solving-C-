#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
ll arr[1010101];
ll tree[4040404];
int N,M,K;

ll merge(ll left, ll right){
    return left + right;
}

ll build(int start=1, int end=N, int node=1) {
    if (start == end) {
        return tree[node] = arr[start-1];
    }
    int mid = start + end >> 1; 
    tree[node] = merge(build(start, mid, node << 1), build(mid+1, end, node<<1|1));
}

void update(int index, ll value, int start=1, int end=N, int node=1){
    if (start == end) {
        tree[node] = value;
        return;
    }
    int mid = start + end >> 1;
    if (index <= mid) update(index, value, start, mid, node<<1);
    else update(index, value, mid+1, end, node<<1|1);
    tree[node] = merge(tree[node<<1], tree[node<<1|1]);
}

ll query(int L, int R, int start=1, int end=N, int node=1) {
    if (end < L || R < start) return 0;
    if (L <= start && end <= R) return tree[node];
    int mid = start + end >> 1;
    return merge(query(L, R, start, mid, node<<1),
             query(L, R, mid+1, end, node<<1|1));
}


int main(){
    fastio
    cin >> N >> M >> K;
    for (int i=0; i<N; ++i) cin >> arr[i];
    build();
    int op; ll b, c;
    for (int i=0; i<M+K; ++i) {
        cin >> op >> b >> c;
        if (op == 1) {
            update(b, c);
        } else {
            cout << query(b, c) << '\n';
        }
    }
}