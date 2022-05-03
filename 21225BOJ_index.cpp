#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    Node *l, *r;
    int sm;
    Node() {
        l = r = nullptr; sm = 0;
    }
    Node(Node* prev) {
        l = r = nullptr;
        sm = prev? prev->sm : 0;
    }
};


Node *tree[808080];
int arr[202020];
int n,m;

Node* build(int s=1, int e=200000) {
    Node *x = new Node();
    if (s == e) return x;
    int mid = s + e >> 1;
    x->l = build(s, mid);
    x->r = build(mid+1, e);
    x->sm = x->l->sm + x->r->sm;
    return x;
}

void update(Node *x, Node *p, int i, int z, int s=1, int e=200000){
    if (s == e) {
        x->sm += z;
        return;
    }
    int mid = s + e >> 1;
    if (i <= mid) {
        x->l = new Node(p->l);
        x->r = p->r;
        update(x->l, p->l, i, z, s, mid);
    } else {
        x->r = new Node(p->r);
        x->l = p->l;
        update(x->r, p->r, i, z, mid+1, e);
    }
    x->sm = x->l->sm + x->r->sm;
}

int kth(Node *l, Node *r, int k, int s=1, int e=200000){
    if (s == e) return s;
    int mid = s + e >> 1;
    int diff = (r->l? r->l->sm : 0) - (l->l? l->l->sm : 0);
    if (k<=diff) return kth(l->l, r->l, k, s, mid);
    return kth(l->r, r->r, k-diff, mid+1, e);
}

int find_h(int n, Node *l, Node *r){
    int lo = 1, hi = n;
    while (lo < hi){
        int mid = lo + hi >> 1;
        if (kth(l, r, mid) < n-mid+1) lo = mid+1;
        else hi = mid;
    }
    return n-lo+1;
}


int main(){
    fastio
    cin >> n >> m;
    tree[0] = build();
    for (int i=1; i<=n; ++i) {
        tree[i] = new Node();
        int x; cin >> x;
        update(tree[i], tree[i-1], x, 1);
    }

    while (m--){
        int x,y; cin >> x >> y;
        cout << find_h(y-x+1, tree[x-1], tree[y]) << ' ';
    }

}