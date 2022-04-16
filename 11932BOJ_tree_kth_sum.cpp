#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <cassert>
#define all(v) v.begin(), v.end()
#define LOG 18
#define INF 1000000
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


using namespace std;
vector<int> arr, dep;

vector<bool> vst;
vector<vector<int>> g, pr;
int n,m;


void find_parent(){
    for (int i=1; i<LOG; ++i)
        for (int j=1; j<=n; ++j) pr[j][i] = pr[pr[j][i-1]][i-1];
}

int lca(int a, int b){
    if (dep[a] < dep[b]) swap(a,b);
    for (int i = LOG-1; i>=0; --i) if (dep[a]-dep[b] >= (1<<i)) a = pr[a][i];
    for (int i = LOG-1; i>=0; --i) if (pr[a][i] != pr[b][i]) {
        a = pr[a][i]; b = pr[b][i];
    }
    if (a == b) return a;
    return pr[a][0];
}

struct Node
{
    Node *l, *r;
    int cnt, lo, hi;
    Node(int lo, int hi) : lo(lo), hi(hi){
        l = r = nullptr;
        cnt = 0;
    }
};


struct PST
{
    vector<Node*> roots;
    void init(int n){
        roots.resize(n+1);
        roots[0] = init(0, INF);
    }
    void update(int p, int x, int i){
        roots[x] = new Node(0, INF);
        update(roots[p], roots[x], i);
    }

    int query(int a, int b, int k){
        int l = lca(a,b);
        int p = pr[l][0];
        return query(roots[a], roots[b], roots[l], roots[p], k);
    }

private:
    Node* init(int lo, int hi){
        Node* x = new Node(lo, hi);
        if (lo == hi) return x;
        int mid = lo + hi >> 1;
        x->l = init(lo, mid);
        x->r = init(mid+1, hi);
        return x;
    }

    void update(Node *p, Node *x, int i){
        if (x->lo == x->hi) {
            if (!x->cnt && p->cnt) x->cnt = p->cnt;
            else x->cnt++;
            return;
        }
        int mid = x->lo + x->hi >> 1;
        if (i <= mid){
            x->l = new Node(x->lo, mid);
            x->r = p->r;
            update(p->l, x->l, i);
        } else {
            x->r = new Node(mid+1, x->hi);
            x->l = p->l;
            update(p->r, x->r, i);
        }
        x->cnt = x->l->cnt + x->r->cnt;
    }

    int query(Node *a, Node *b, Node *l, Node *p, int k){
        if (a->lo == a->hi) return a->lo;
        int diff = a->l->cnt + b->l->cnt - l->l->cnt - p->l->cnt;
        if (k > diff) return query(a->r, b->r, l->r, p->r, k-diff);
        else return query(a->l, b->l, l->l, p->l, k);
    }

} tree ;


void dfs(int node = 1){
    for (auto &next : g[node]){
        if (!vst[next]){
            vst[next] = 1;
            pr[next][0] = node;
            dep[next] = dep[node] + 1;
            tree.update(node, next, arr[next-1]);
            dfs(next);
        }
    }
}


int main()
{
    fastio
    cin >> n;
    arr.resize(n); pr.resize(n+1); g.resize(n+1);
    tree.init(n); dep.resize(n+1);
    for (int i=0; i<=n; ++i) pr[i].resize(LOG);
    for (int i=0; i<n; ++i) cin >> arr[i];
    for (int i=n-1; i--;) {
        int x, y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }

    cin >> m;
    tree.update(0,1,arr[0]);
    vst.resize(n+1);
    vst[1] = 1;
    dfs(); find_parent();

    while (m--){
        int x,y,k; cin >> x >> y >> k;
        cout << tree.query(x,y,k) << '\n';
    }



} // namespace std;
