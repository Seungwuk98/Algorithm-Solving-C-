#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <bits/stdc++.h>
#include <set>
#include <string>

using namespace std;

int n,q,pv=0;
vector<tuple<string,int,int,int>> query;
vector<string> result;
vector<int> in, peng, pengtoin, depth, top, parent, rnk, sz;
vector<vector<int>> g;


struct SegTree{
    vector<int> tree;
    void init(){
        tree.resize(2*n);
        for (int i=0; i<n; ++i){
            tree[i+n] = pengtoin[i];
        }
        for (int i=n-1; i; --i){
            tree[i] = tree[i<<1] + tree[i<<1|1];
        }
    }
    void update(int i, int v){
        tree[i+=n] = v;
        for (;i>1; i>>=1) tree[i>>1] = tree[i] + tree[i^1]; 
    }
    int sum(int l, int r){
        int ret = 0;
        for (l+=n, r+=n+1;l<r;l>>=1, r>>=1){
            if (l&1) ret += tree[l++];
            if (r&1) ret += tree[--r]; 
        } return ret;
    }
}tree;

int find(int node){
    if (parent[node] == node) return node;
    parent[node] = find(parent[node]);
    return parent[node];
}

string Union(int node1, int node2){
    int root1 = find(node1), root2 = find(node2);
    if (root1 == root2) return "no";
    if (rnk[root1] < rnk[root2]) {
        parent[root1] = root2;
    }
    else{
        parent[root2] = root1;
        if (rnk[root1]==rnk[root2]) rnk[root1]++;
    } return "yes";
}

vector<bool> vst;


void dfs1(int node = 0){
    int msize = 0; int midx = 0;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (!vst[next]){
            vst[next] = true;
            depth[next] = depth[node]+1;
            parent[next] = node;
            dfs1(next); sz[node] += sz[next];
            if (sz[next] > msize){
                msize = sz[next]; midx = i;
            }
        }
    }
    if (!g[node].empty()) swap(g[node][0], g[node][midx]);
}

void dfs2(int node = 0){
    in[node] = pv++;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (!vst[next]){
            vst[next] = true;
            top[next] = i? next : top[node];
            pengtoin[pv] = peng[next];
            dfs2(next);
        }
    }
}

int excursion(int a, int b){
    int ret = 0;
    while (top[a]!=top[b]){
        if (depth[top[a]] < depth[top[b]]) swap(a,b);
        int st = top[a];
        ret += tree.sum(in[st], in[a]);
        a = parent[st];
    }
    if (depth[a] > depth[b]) swap(a,b);
    ret += tree.sum(in[a], in[b]);
    return ret;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n; in.resize(n); peng.resize(n); pengtoin.resize(n); sz.resize(n,1);
    depth.resize(n); top.resize(n); parent.resize(n); rnk.resize(n); g.resize(n);
    for (int i=0; i<n; i++){
        parent[i] = i; top[i] = i; cin >> peng[i];
    }
    cin >> q;
    query.resize(q); result.resize(q);
    for (int i=0; i<q; ++i){
        string qry; int a; int b;
        cin >> qry >> a >> b; a--;
        if (qry == "excursion") {
            if (find(a) != find(--b)) result[i] = "impossible";
        } else if (qry == "bridge"){
            result[i] = Union(a,--b);
            g[a].push_back(b);
            g[b].push_back(a);
        } else if (qry == "penguins"){
            swap(peng[a], b);
        }
        query.push_back(make_tuple(qry, a, b, i));
    }
    reverse(query.begin(), query.end());
    
    



    vst.resize(n, false);
    for (int i=0; i<n; ++i){
        if (!vst[i]){
            vst[i] = true;
            dfs1(i);
        }
    }
    vst.assign(n,false);
    for (int i=0; i<n; ++i){
        if (!vst[i]){
            vst[i] = true;
            pengtoin[pv] = peng[i];
            dfs2(i);
        }
    }    
    tree.init();
    for (auto t : query){
        string qry = get<0>(t); int a = get<1>(t), b = get<2>(t), idx = get<3>(t);
        if (qry == "excursion"){
            if (result[idx] != "impossible") result[idx] = to_string(excursion(a,b));
        } else if(qry == "penguins") tree.update(in[a], b);
    }

    for (auto x : result){
        if (x!="") cout << x << '\n';
    }


} // namespace std;
