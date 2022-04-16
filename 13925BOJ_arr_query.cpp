#include <bits/stdc++.h>
#include <vector>

using ull = unsigned long long;
using namespace std;

vector<ull> arr;
ull D = 1000000007;
int n, m;

struct Node{
    ull data;
    ull lazy1, lazy2;
    int lo, hi;
    Node *l, *r;
    Node(int lo, int hi) 
        : lo(lo), hi(hi), l(nullptr), r(nullptr), lazy1(0), lazy2(1){}
};

struct SegTree
{
    Node *root;
    Node* init(int lo, int hi){
        Node* x =new Node(lo, hi);
        if (lo == hi){
            x->data = arr[hi-1];
            return x;
        } 
        int mid = (lo+hi)/2;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        x->data = (x->l->data + x->r->data)%D;
        return x;
    }
    void init(){
        root = init(1,n);
    }

    void update(int l, int r, ull pl, ull mul){
        if (l>r) swap(l,r);
        update_do(root, l, r, pl, mul);
    }

    void update_do(Node* x, int l, int r, ull pl, ull mul){
        prop(x);
        if (x->lo == l && x->hi == r){
            x->lazy1 += pl; x->lazy2 *= mul;
            x->lazy1 %= D; x->lazy2 %= D;
            prop(x);
            return;
        }
        int mid = x->hi + x->lo >> 1;
        if (r <= mid) {
            update_do(x->l, l, r, pl, mul);
            prop(x->r);
        } else if (l > mid){
            update_do(x->r, l, r, pl, mul);
            prop(x->l);
        } else{
            update_do(x->l, l, mid, pl, mul);
            update_do(x->r, mid+1, r, pl, mul);
        }
        x->data = (x->l->data + x->r->data)%D;
    }

    ull isum(int l, int r){
        if (l>r) swap(l,r);
        return sum_do(root, l, r);
    }

    ull sum_do(Node* x, int l, int r){
        prop(x);
        if (x->lo == l && x->hi == r) return x->data;
        int mid = x->lo + x->hi >> 1;
        if (r <= mid){
            prop(x->r);
            return sum_do(x->l, l, r);
        } else if (l > mid){
            prop(x->l);
            return sum_do(x->r, l, r);
        } else{
            return (sum_do(x->l, l, mid) + sum_do(x->r, mid+1, r))%D;
        }
    }    

    void prop(Node* x){
        if (x->lazy1 == 0 && x->lazy2 == 1) return;
        int c = x->hi - x->lo +1;
        x->data = (x->data * x->lazy2%D + x->lazy1 * c%D)%D;
        if (x->l && x->r){
            x->l->lazy1 *= x->lazy2; x->l->lazy1 %= D;
            x->l->lazy1 += x->lazy1; x->l->lazy1 %= D;
            x->l->lazy2 *= x->lazy2; x->l->lazy2 %= D;
            x->r->lazy1 *= x->lazy2; x->r->lazy1 %= D;
            x->r->lazy1 += x->lazy1; x->r->lazy1 %= D;
            x->r->lazy2 *= x->lazy2; x->r->lazy2 %= D;
        }
        x->lazy1 = 0; x->lazy2 =1;
    }

}tree;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i=n;i;i--){
        ull x; cin >> x;
        arr.push_back(x);
    }
    tree.init();
    cin >> m;
    while (m--){
        int q,x,y; ull v;
        cin >> q >> x >> y;
        if (q != 4) cin >> v;
        if (q == 1) tree.update(x,y,v,1);
        else if (q == 2) tree.update(x,y,0,v);
        else if (q == 3) tree.update(x,y,v,0);
        else cout << tree.isum(x,y) << '\n';
    }


} // namespace std;
