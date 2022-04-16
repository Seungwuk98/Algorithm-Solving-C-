#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;


struct Node
{
    Node *l, *r;
    ll sum; int lo, hi;
    Node(int lo, int hi) : lo(lo), hi(hi){
        sum = 0;
        l=r=nullptr;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};

vector<vector<int>> mat;
int n,m,q;

struct PST
{
    vector<Node*> roots;
    int last=0;

    void init(int n){
        roots[0] = init(1, n);
    }

    void update(){
        for (int i=1; i<=m; ++i) {
            roots[i] = new Node(1,n);
            for (int j=1; j<=n; ++j){
                update(roots[i-1], roots[i], j, mat[i-1][j-1]);
            }
        }
    }

private:

    Node* init(int lo, int hi){
        Node *x = new Node(lo, hi);
        if (lo == hi) return x;
        int mid = lo + hi >> 1;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        return x;
    }

    void update(Node *p, Node *x, int i, ll z){
        if (x->lo == x->hi) {
            x->sum += z; return;
        }
        int mid = x->lo + x->hi >> 1;
        if (i <= mid){
            x->r = p->r;
            if (!x->l) x->l = new Node(x->lo, mid);
            update(p->l, x->l, i, z);
        } else {
            x->l = p->l;
            if (!x->r) x->r = new Node(mid+1, x->hi);
            update(p->r, p->r, i, z);
        }
        x->sum = x->l->sum + x->r->sum;
    }



};



int main()
{
    
} // namespace std;
