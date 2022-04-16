#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
#define INF 100005

using namespace std;
using ll = long long;
struct Node
{
    int lo, hi;
    Node *l, *r;
    ll cnt;
    Node(int lo, int hi) : lo(lo), hi(hi){
        l = r = nullptr;
        cnt = 0;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};

struct PST
{
    vector<Node*> roots;

    void init(){
        roots.clear();
        roots.resize(INF);
        roots[0] = init(0, INF);
    }

    void update(int x){
        roots[x] = roots[x-1];
    }

    void update(int x, int y){
        if (!roots[x]) roots[x] = new Node(0, INF);
        update(roots[x-1], roots[x], y);
    }

    ll query(int u, int d, int l, int r){
        return query(roots[u-1], roots[d], l, r);
    }

    void print(int i){
        print(roots[i]);
        cout << '\n';
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

    void update(Node *p, Node *x, int y){
        if (x->lo == x->hi) {
            if (!x->cnt) x->cnt = p->cnt+1;
            else x->cnt ++;
            return;
        }
        int mid = x->lo + x->hi >> 1;
        if (y<=mid) {
            if (!x->l || x->l == p->l) x->l = new Node(x->lo, mid);
            if (!x->r) x->r = p->r;
            update(p->l, x->l, y);
        } else {
            if (!x->l) x->l = p->l;
            if (!x->r || x->r == p->r) x->r = new Node(mid+1, x->hi);
            update(p->r, x->r, y);
        }
        x->cnt = x->l->cnt + x->r->cnt;
    }
    
    ll query(Node *up, Node *dn, int l, int r){
        if (dn->lo == l && dn->hi == r) return dn->cnt - up->cnt;
        int mid = dn->lo + dn->hi >> 1;
        if (r <= mid) return query(up->l, dn->l, l, r);
        else if (l > mid) return query(up->r, dn->r, l, r);
        else return query(up->l, dn->l, l, mid) + query(up->r, dn->r, mid+1, r);
    }

    void print(Node *x){
        if (!x->l && !x->r) {
            cout << x->cnt << ' ';
            return;
        } 
        print(x->l);
        print(x->r);
    }
} pst;

struct p{
    int x, y;
    bool operator<(const p &t) const{
        if (x != t.x) return x<t.x;
        return y<t.y;
    }
};

int main()
{
    fastio
    int T; cin >> T;
    while (T--){
        int n,m; cin >> n >> m;
        pst.init();
        vector<p> pt;
        for (int i=0; i<n; ++i){
            int x,y; cin >> x >> y;
            pt.push_back(p{++x,++y});
        }
        sort(all(pt));
        for (int i=1, j=0; i<INF; ++i){
            bool c = 0;
            while (j<n && pt[j].x == i){
                pst.update(i, pt[j].y);
                j++; c = 1;
            }
            if (!c) pst.update(i);
        }
        ll ret = 0;
        while (m--){
            int u,d,l,r; cin >> u >> d >> l >> r;
            ret += pst.query(++u, ++d, ++l, ++r);
        }
        cout << ret << '\n';
    }

} // namespace 
