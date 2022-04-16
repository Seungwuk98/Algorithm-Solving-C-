#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using ll = long long;
using namespace std;

struct Node
{
    ll mx, mn, sm;
    ll lazy1, lazy2;
    Node() {
        mx = mn = sm = 0;
        lazy1 = lazy2 = 0;
    }
    Node(ll x) {
        mx = mn = sm = x;
        lazy1 = lazy2 = 0;
    }
};

vector<Node> tree(404040);

Node merge(Node &A, Node &B){
    Node ret;
    ret.mn = min(A.mn, B.mn);
    ret.mx = max(A.mx, B.mx);
    ret.sm = A.sm + B.sm;
    return ret;
}

void build(int s, int e, vector<int> &arr, int x = 1){
    if (s == e) {
        tree[x] = Node(arr[s-1]);
        return;        
    }
    int mid = s + e >> 1;
    build(s, mid, arr, x<<1); build(mid+1, e, arr, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void prop(int x, int s, int e){
    if (!tree[x].lazy1 && !tree[x].lazy2) return;
    if (tree[x].lazy1 && !tree[x].lazy2){
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
    tree[x].lazy1 = tree[x].lazy2 = 0;
}

ll query(int l, int r, int s, int e, int x = 1){
    prop(x, s, e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x].sm;
    int mid = s + e >> 1;
    return query(l, r, s, mid, x<<1) + query(l, r, mid+1, e, x<<1|1);
}

void update_pl(int l, int r, int s, int e, int k, int x = 1){
    prop(x, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        tree[x].lazy1 += k;
        prop(x, s, e); 
        return;
    }
    int mid = s + e >> 1;
    update_pl(l, r, s, mid, k, x<<1); update_pl(l, r, mid+1, e, k, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void update_sq(int l, int r, int s, int e, int x = 1){
    prop(x, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        if ((ll)(sqrt(tree[x].mx)) == (ll)(sqrt(tree[x].mn))){
            tree[x].lazy1 = 0;
            tree[x].lazy2 = (ll)(sqrt(tree[x].mx));
            prop(x, s, e); return;
        }
        if (tree[x].mx == tree[x].mn+1){
            tree[x].lazy1 -= tree[x].mn - (ll)(sqrt(tree[x].mn));
            prop(x, s, e); return;
        }
    }
    int mid = s + e >> 1;
    update_sq(l, r, s, mid, x<<1); update_sq(l, r, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}


int main()
{
    fastio
    int n,m;
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    build(1, n, arr);
    cin >> m;
    while (m--){
        int op, l, r, x;
        cin >> op >> l >> r;
        if (op == 1){
            cin >> x;
            update_pl(l, r, 1, n, x);
        } else if (op == 2){
            update_sq(l, r, 1, n);
        } else {
            cout << query(l, r, 1, n) << '\n';
        }
    }

} // namespace std;
