#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N;
ll tree[1<<19]; // N보다 큰 가장 작은 2의 제곱수의 2배라 가정 2^19

void build(vector<ll> &arr, int start=1, int end=N, int node=1){
    if (start == end){
        tree[node] = arr[start-1];
        return;
    }
    int mid = start + end >> 1;
    build(arr, start, mid, node<<1); 
    build(arr, mid+1, end, node<<1|1);
    tree[node] = tree[node<<1] + tree[node<<1|1];
}


void update(int idx, int plus, int start=1, int end=N, int node=1){
    if (start == end){
        tree[node] += plus;
        return;
    }
    int mid = start + end >> 1;
    if (idx <= mid){
        update(idx, plus, start, mid, node<<1);
    } else {
        update(idx, plus, mid+1, end, node<<1|1);
    }
    tree[node] = tree[node<<1] + tree[node<<1|1];
}

ll query(int l, int r, int start=1, int end=N, int node=1){
    if (end < l || r < start) return 0;
    if (l <= start && end <= r) return tree[node];
    int mid = start + end >> 1;
    return query(l, r, start, mid, node<<1) + query(l, r, mid+1, end, node<<1|1);
}




