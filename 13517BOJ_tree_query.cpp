#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
#define INF 1000001
#define LOG 18

using namespace std;
int n,m;
vector<int> arr, dep;
vector<bool> vst;
vector<vector<int>> pr, g;

int lca(int a, int b){
    if (dep[a] < dep[b]) swap(a,b);
    for (int i=LOG-1; i>=0; --i) if (dep[a]-dep[b] >= (1<<i)) a=pr[a][i];
    if (a==b) return a;
    for (int i=LOG-1; i>=0; --i) if (pr[a][i]!=pr[b][i]) {
        a = pr[a][i]; b = pr[b][i];
    }
    return pr[a][0];
}


struct Node
{
    Node *l, *r;
    int lo, hi, cnt;
    Node(int lo, int hi) : lo(lo), hi(hi){
        l=r=nullptr;
        cnt = 0;
    }
    Node(int lo, int hi, int v) : lo(lo), hi(hi), cnt(v){
        l=r=nullptr;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};

struct PST
{
    vector<Node*> tree;
    void init(){
        tree.resize(INF);
        tree[0] = init(1,INF);
    }

    void update(int p, int x){
        if (!tree[x]) tree[x] = new Node(1,INF);
        update(tree[p], tree[x], arr[x-1]);
    }

    int query(int a, int b, int k){
        int l = lca(a,b);
        int p = pr[l][0];
        return query(tree[p], tree[l], tree[a], tree[b], k);
    }

private:
    Node* init(int lo, int hi){
        Node *x = new Node(lo,hi);
        if (lo == hi) return x;
        int mid = lo + hi >> 1;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        return x;
    }

    void update(Node *p, Node *x, int z){
        if (x->lo == x->hi){
            x->cnt++; return;
        }
        int mid = x->lo + x->hi >> 1;
        if (z <= mid){
            if (!x->l || x->l == p->l) x->l = new Node(x->lo, mid, p->l->cnt);
            if (!x->r) x->r = p->r;
            update(p->l, x->l, z);
        } else {
            if (!x->l) x->l = p->l;
            if (!x->r || x->r == p->r) x->r = new Node(mid+1, x->hi, p->r->cnt);
            update(p->r, x->r, z);
        }
        x->cnt = x->l->cnt + x->r->cnt;
    }

    int query(Node *p, Node *l, Node *a, Node *b, int k){
        if (p->lo == p->hi) return p->lo;
        int diff = a->l->cnt + b->l->cnt - l->l->cnt - p->l->cnt;
        if (k > diff) return query(p->r, l->r, a->r, b->r, k-diff);
        else return query(p->l, l->l, a->l, b->l, k);
    }
} pst;

void dfs(int x = 1){
    for (int &t : g[x]){
        if (!vst[t]){
            vst[t] = 1;
            dep[t] = dep[x] + 1;
            pr[t][0] = x;
            pst.update(x, t);
            dfs(t);
        }
    }
}

void parent(){
    for (int i=1; i<LOG; ++i)
        for (int j=1; j<=n; ++j)
            pr[j][i] = pr[pr[j][i-1]][i-1];
}

int main()
{
    fastio
    cin >> n;
    arr.resize(n); pr.resize(n+1); g.resize(n+1); vst.resize(n+1); dep.resize(n+1);
    for (int i=0; i<=n; ++i) pr[i].resize(LOG);
    for (int i=0; i<n; ++i) cin >> arr[i];
    for (int i=n-1; i--;){
        int x,y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    pst.init();
    vst[1] = 1;
    pst.update(0,1);
    dfs();
    parent();

    cin >> m;
    while (m--){
        int a,b,k; cin >> a >> b >> k;
        cout << pst.query(a,b,k) << '\n';
    }

} // namespace std;
