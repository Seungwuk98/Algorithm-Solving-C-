#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<int> arr;

struct Node{
    Node *l, *r;
    int data, d,u, lazy, mid;
    Node(int _d, int _u)
     : d(_d), u(_u), l(nullptr), r(nullptr){
        mid = (d+u)/2;
        lazy = 0;
    }
};

struct SegTree{
    Node *root;
    Node* init(int d, int u){
        Node* node = new Node(d,u);
        if (d==u) {
            node->data = arr[u];
            return node;
        }
        int mid = node->mid;
        node->l = init(d,mid);
        node->r = init(mid+1,u);
        node->data = node->l->data^node->r->data;
        return node;
    }
    void init(){
        root = init(0,n-1);
    }
    void do_update(Node* node, int l, int r, int k){
        if (node->d == l && node->u == r){
            node->lazy^=k; return;
        }
        int c = r-l+1;
        if (c&1) node->data ^= k;
        if (r <= node->mid) do_update(node->l,l,r,k);
        else if (l > node->mid) do_update(node->r,l,r,k);
        else {
            do_update(node->l,l,node->mid,k);
            do_update(node->r,node->mid+1,r,k);
        }
    }
    void query1(int q, int l, int r, int k){
        do_update(root, l, r, k);
    }
    void prop(Node* node){
        int c = node->u - node->d +1;
        if (c&1) node->data ^= node->lazy;
        if (node->l) node->l->lazy ^= node->lazy;
        if (node->r) node->r->lazy ^= node->lazy;
        node->lazy = 0;
    }
    
    int do_find(Node* node, int l, int r){
        if (node->lazy) prop(node);
        if (node->d == l && node->u == r) return node->data;
        int left, right;
        left=right=0;
        if (r <= node->mid) left = do_find(node->l, l, r);
        else if (l > node->mid) right = do_find(node->r,l,r);
        else {
            left = do_find(node->l,l,node->mid);
            right = do_find(node->r,node->mid+1,r);
        }
        return left^right;
    }

    int query2(int q, int l, int r){
        return do_find(root, l, r);
    }

}tree;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i=n;i;i--) {
        int x; cin >> x;
        arr.push_back(x);
    }
    tree.init();
    cin >> m;
    while (m--){
        int q; cin >> q;
        if (q==1){
            int a, b, k; cin >> a >> b >> k;
            if (a>b) swap(a,b);
            tree.query1(1,a,b,k);
        } else{
            int a, b; cin >> a >> b;
            if (a>b) swap(a,b);
            cout << tree.query2(2,a,b) << '\n';
        }
    }

} // namespace std;
