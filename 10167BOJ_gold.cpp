#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#define all(v) v.begin(), v.end()

using ll = long long;
using namespace std;

struct Node
{
    int lo, hi;
    ll lmax, rmax, max, sum;
    Node *l, *r;
    Node(int lo, int hi) : lo(lo), hi(hi){
        lmax = rmax = max = sum = 0;
    }
    void reset(){
        lmax = rmax = max = sum = 0;
    }
};

struct SegTree
{
    Node *root;
    void init(){
        root = init(0, 3000);
    }

    Node* init(int lo, int hi){
        Node *node = new Node(lo, hi);
        if (lo == hi) return node;
        int mid = lo + hi >> 1;
        node->l = init(lo, mid);
        node->r = init(mid+1, hi);
        return node;
    }

    void reset(){
        do_reset(root);
    }

    void update(int x, ll w){
        do_update(root, x, w);
    }
    
    ll query(){
        return root->max;
    }

private:
    void do_update(Node *node, int x, ll w){
        if (node->lo == node->hi) {
            node->lmax = node->rmax = node->max = node->sum += w;
            return;
        } 
        int mid = node->lo + node->hi >> 1;
        do_update(x<=mid? node->l : node->r, x, w);
        node->sum = node->l->sum + node->r->sum;
        node->lmax = max(node->l->lmax, node->l->sum + node->r->lmax);
        node->rmax = max(node->r->rmax, node->r->sum + node->l->rmax);
        node->max = max({node->l->max, node->r->max, node->l->rmax + node->r->lmax});
    }

    void do_reset(Node *node){
        node->reset();
        if (node->lo == node->hi) return;
        do_reset(node->l);
        do_reset(node->r);
    }
} tree;

int n;
struct p
{
    int x,y;
    ll w;
    bool operator< (const p &t) const{
        if (y != t.y) return y < t.y;
        return x < t.x;
    }
};

vector<p> point;
vector<int> x_sort;
vector<int> y_sort;

int main()
{
    cin >> n;
    for (int i=0; i<n; ++i){
        int x,y; ll z;
        cin >> x >> y >> z;
        p d{x,y,z};
        point.push_back(d);
        x_sort.push_back(x); y_sort.push_back(y);
    }
    sort(all(x_sort));
    sort(all(y_sort));
    x_sort.erase(unique(all(x_sort)), x_sort.end());
    y_sort.erase(unique(all(y_sort)), y_sort.end());
    for (auto &t : point){
        t.x = lower_bound(all(x_sort), t.x) - x_sort.begin();
        t.y = lower_bound(all(y_sort), t.y) - y_sort.begin();
    }
    sort(point.begin(), point.end());
    tree.init();
    ll result = 0;
    for (int i=0; i<n; ++i){
        if (i && point[i].y == point[i-1].y) continue;
        tree.reset();
        for (int j=i; j<n; ++j){
            tree.update(point[j].x, point[j].w);
            if (j==n-1 || point[j].y != point[j+1].y)
                result = max(result, tree.root->max);
        }
    }
    cout << result << '\n';
    
    

} // namespace std;
