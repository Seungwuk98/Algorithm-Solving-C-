#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N;
struct Node
{
    ll sum, lazy;
    Node(){
        sum = lazy = 0;
    }
};

Node tree[1<<19]; // N보다 큰 가장 작은 2의 제곱수의 2배라 가정 2^19

void build(vector<ll> &arr, int start=1, int end=N, int node=1){
    if (start == end){
        tree[node].sum = arr[start-1];
        return;
    }
    int mid = start + end >> 1;
    build(arr, start, mid, node<<1); 
    build(arr, mid+1, end, node<<1|1);
    tree[node].sum = tree[node<<1].sum + tree[node<<1|1].sum;
}

void propagation(int node, int start, int end){
    if (!tree[node].lazy) return;
    tree[node].sum += (end - start + 1) * tree[node].lazy;
    if (start ^ end){
        tree[node<<1].lazy += tree[node].lazy;
        tree[node<<1|1].lazy += tree[node].lazy;
    }
    tree[node].lazy = 0;
}

void update_range(int plus, int l, int r, int start=1, int end=N, int node=1){
    propagation(node, start, end);
    if (end < l || r < start) return;
    if (l <= start && end <= r) {
        tree[node].lazy += plus;
        propagation(node, start, end);
        return;
    }
    int mid = start + end >> 1;
    update_range(plus, l, r, start, mid, node<<1);
    update_range(plus, l, r, mid+1, end, node<<1|1);
    tree[node].sum = tree[node<<1].sum + tree[node<<1|1].sum;
    
}

void update_point(int idx, int plus, int start=1, int end=N, int node=1){
    propagation(node, start, end);
    if (start == end){
        tree[node].sum += plus;
        return;
    }
    int mid = start + end >> 1;
    if (idx <= mid) update_point(idx, plus, start, mid, node<<1);
    else update_point(idx, plus, mid+1, end, node<<1|1);
    tree[node].sum = tree[node<<1].sum + tree[node<<1|1].sum;
}

ll query(int l, int r, int start=1, int end=N, int node=1){
    propagation(node, start, end);
    if (end < l || r < start) return 0;
    if (l <= start && end <= r) return tree[node].sum;
    int mid = start + end >> 1;
    return query(l, r, start, mid, node<<1) + query(l, r, mid+1, end, node<<1|1);
}




