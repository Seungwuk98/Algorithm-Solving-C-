#include <bits/stdc++.h>
#define INF 2000000001LL
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define div(x,d) floor(x/(double)d)

using namespace std;
using ll = long long;

struct Node
{
    ll mx, mn, sm, lazy1, lazy2;
    Node(){
        mx = mn = sm = lazy1 = 0;
        lazy2 = INF;
    }
    Node(int x) {
        mx = mn = sm = x;
        lazy1 = 0;
        lazy2 = INF;
    }
};

Node merge(Node &A, Node &B){
    Node ret;
    ret.mn = min(A.mn, B.mn);
    ret.mx = max(A.mx, B.mx);
    ret.sm = A.sm + B.sm;
    return ret;
}

Node tree[404040];
int n,q;

void build(vector<ll> &arr, int s=0, int e=n-1, int x = 1){
    if (s == e) {
        tree[x] = Node(arr[s]);
        return;
    }
    int mid = s + e >> 1;
    build(arr, s, mid, x<<1); build(arr, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void prop(int x, int s, int e){
    if (!tree[x].lazy1 && tree[x].lazy2 == INF) return;
    if (tree[x].lazy1 && tree[x].lazy2 == INF){
        tree[x].sm += (e-s+1) * tree[x].lazy1;
        tree[x].mx += tree[x].lazy1;
        tree[x].mn += tree[x].lazy1;
        if (s ^ e) {
            tree[x<<1].lazy1 += tree[x].lazy1;
            tree[x<<1|1].lazy1 += tree[x].lazy1;
        } 
    } else {
        tree[x].sm = (e-s+1) * (tree[x].lazy2 + tree[x].lazy1);
        tree[x].mx = tree[x].mn = tree[x].lazy2 + tree[x].lazy1;
        if (s ^ e) {
            tree[x<<1].lazy1 = tree[x<<1|1].lazy1 = 0;
            tree[x<<1].lazy2 = tree[x<<1|1].lazy2 = tree[x].lazy2 + tree[x].lazy1;
        }
    }
    tree[x].lazy1 = 0;
    tree[x].lazy2 = INF;
}

void update_pl(int l, int r, ll z, int s=0, int e=n-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return;
    if (l <= s && e <= r){
        tree[x].lazy1 = z;
        prop(x, s, e); return;
    }
    int mid = s + e >> 1;
    update_pl(l, r, z, s, mid, x<<1); update_pl(l, r, z, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void update_div(int l, int r, ll z, int s=0, int e=n-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return;
    if (l <= s && e <= r){
        if (div(tree[x].mn,z) == div(tree[x].mx,z)){
            tree[x].lazy1 = 0;
            tree[x].lazy2 = div(tree[x].mn,z);
            prop(x,s,e);
            return;
        }
        if (tree[x].mn >= 0 && tree[x].mn + 1 == tree[x].mx){
            tree[x].lazy1 -= tree[x].mn - div(tree[x].mn,z);
            prop(x,s,e);
            return;
        }
    }
    int mid = s + e >> 1;
    update_div(l, r, z, s, mid, x<<1); update_div(l, r, z, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

ll query_min(int l, int r, int s=0, int e=n-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return INF;
    if (l <= s && e <= r) return tree[x].mn;
    int mid = s + e >> 1;
    return min(query_min(l, r, s, mid, x<<1), query_min(l, r, mid+1, e, x<<1|1)); 
}

ll query_sum(int l, int r, int s=0, int e=n-1, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x].sm;
    int mid = s + e >> 1;
    return query_sum(l, r, s, mid, x<<1) + query_sum(l, r, mid+1, e, x<<1|1);
}

void Print(int s=0, int e=n-1, int x=1){
    prop(x,s,e);
    if (s==e) {
        cout << tree[x].sm << ' ';
        return;
    } 
    int mid = s + e >> 1;
    Print(s, mid, x<<1);
    Print(mid+1, e, x<<1|1);
}

int main()
{
    fastio
    cin >> n >> q;
    vector<ll> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    build(arr);
    while (q--){
        int op,l,r; ll c;
        cin >> op >> l >> r;
        if (op == 1){
            cin >> c;
            update_pl(l, r, c);
        } else if (op == 2){
            cin >> c;
            update_div(l, r, c);
        } else if (op == 3){
            cout << query_min(l,r) << '\n';
        } else {
            cout << query_sum(l,r) << '\n';
        }
    }

} // namespace std;
