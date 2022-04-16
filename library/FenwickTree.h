#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> Fenwick;
int n;

void build(vector<ll> &arr){
    n = arr.size();
    Fenwick.resize(n+1);
    vector<ll> pre(n+1);
    for (int i=0; i<n; ++i) pre[i+1] = pre[i] + arr[i];
    for (int i=1; i<=n; ++i) Fenwick[i] = pre[i] - pre[i&-i];
}

void update(int idx, int plus){
    for (; idx <= n; idx += idx&-idx) Fenwick[idx] += plus;
}

int query_1_to_idx(int idx){
    ll ret = 0;
    for (; idx; idx -= idx&-idx) ret += Fenwick[idx];
    return ret;
}

int query_L_to_R(int L, int R){
    return query_1_to_idx(R) - query_1_to_idx(L-1);
}