#include <bits/stdc++.h>
#include <vector>

using ull = unsigned int;
using namespace std;

vector<int> top, in, out, sz, pr, dep;
vector<vector<int>> g;
int n, q, pv = 0;
vector<bool> vst;

vector<ull> arr;

void dfs1(int node=0){
    int msz, midx;
    msz = midx = 0;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        dep[next] = dep[node]+1;
        pr[next] = node;
        dfs1(next); sz[node] += sz[next];
        if (sz[next] > msz) {
            msz = sz[next]; midx = i;
        }
    }
    if (!g[node].empty()) swap(g[node][0], g[node][midx]);
}

void dfs2(int node=0){
    in[node] = pv++;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        top[next] = i? next : top[node];
        dfs2(next);
    }
    out[node] = pv-1;
}


struct Node{
    ull data;
    ull lazy1, lazy2;
    int lo, hi;
    Node *l, *r;
    Node(int lo, int hi) 
        : data(0), lo(lo), hi(hi), l(nullptr), r(nullptr), lazy1(0), lazy2(1){}
};

struct SegTree
{
    Node *root;
    Node* init(int lo, int hi){
        Node* x =new Node(lo, hi);
        if (lo == hi){
            return x;
        } 
        int mid = (lo+hi)/2;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        return x;
    }
    void init(){
        root = init(0,n-1);
    }

    void update(int l, int r, ull pl, ull mul){
        if (l>r) swap(l,r);
        update_do(root, l, r, pl, mul);
    }

    void update_do(Node* x, int l, int r, ull pl, ull mul){
        prop(x);
        if (x->lo == l && x->hi == r){
            x->lazy1 += pl; x->lazy2 *= mul;
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
        x->data = (x->l->data + x->r->data);
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
            return (sum_do(x->l, l, mid) + sum_do(x->r, mid+1, r));
        }
    }    

    void prop(Node* x){
        if (x->lazy1 == 0 && x->lazy2 == 1) return;
        int c = x->hi - x->lo +1;
        x->data = (x->data * x->lazy2 + x->lazy1 * c);
        if (x->l && x->r){
            x->l->lazy1 *= x->lazy2; 
            x->l->lazy1 += x->lazy1; 
            x->l->lazy2 *= x->lazy2; 
            x->r->lazy1 *= x->lazy2; 
            x->r->lazy1 += x->lazy1; 
            x->r->lazy2 *= x->lazy2; 
        }
        x->lazy1 = 0; x->lazy2 =1;
    }

}tree;

void query_update(int a, int b, ull pl, ull mul){
    while (top[a] != top[b]){
        if (dep[top[a]] < dep[top[b]]) swap(a,b);
        int st = top[a];
        tree.update(in[st], in[a], pl, mul);
        a = pr[st];
    }
    if (dep[a] > dep[b]) swap(a,b);
    tree.update(in[a], in[b], pl, mul);
}

ull query_sum(int a, int b){
    ull ret = 0;
    while (top[a] != top[b]){
        if (dep[top[a]] < dep[top[b]]) swap(a,b);
        int st = top[a];
        ret += tree.isum(in[st], in[a]);
        a = pr[st];
    }
    if (dep[a] > dep[b]) swap(a,b);
    ret += tree.isum(in[a], in[b]);
    return ret;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> q;
    vst.resize(n,0); g.resize(n); top.resize(n); sz.resize(n,1); in.resize(n);
    out.resize(n); pr.resize(n); arr.resize(n); dep.resize(n);
    
    for (int i=n-1; i--;){
        int a,b; cin >> a >> b;
        g[--a].push_back(--b);
        g[b].push_back(a);
    }
    vst[0] = 1;
    dfs1();
    vst.assign(n,0);
    vst[0] = 1;
    dfs2();
    tree.init();
    while (q--){
        int k, x, y; ull v; cin >> k >> x;
        x--;
        switch (k)
        {
        case 1:
            cin >> v; 
            tree.update(in[x],out[x],v,1);
            break;
        case 2:
            cin >> y >> v;
            query_update(x,--y,v,1);
            break;
        case 3:
            cin >> v;
            tree.update(in[x], out[x],0,v);
            break;
        case 4:
            cin >> y >> v;
            query_update(x,--y,0,v);
            break;
        case 5:
            cout << tree.isum(in[x],out[x]) << '\n';
            break;
        case 6:
            cin >> y;
            cout << query_sum(x, --y) << '\n';
            break;
        }
    }


} // namespace std;
