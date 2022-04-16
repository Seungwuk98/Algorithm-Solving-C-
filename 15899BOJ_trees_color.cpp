#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;
using ull = unsigned long long;
vector<int> arr, in, out, arrin;
int n, m, c, pv=0;

vector<vector<int>> g;
vector<bool> vst;

void dfs(int node = 1){
    in[node] = pv;
    arrin[pv++] = arr[node-1];
    for (int &next : g[node]){
        if (vst[next]) continue;
        vst[next] = 1;
        dfs(next);
    } out[node] = pv;
}


void merge(vector<int> &ret, vector<int> &a, vector<int> &b){
    int i, j; i=j=0;
    int al = a.size(), bl = b.size();
    while (1){
        if (i == al){
            while (j < bl) ret.push_back(b[j++]);
            break;
        } else if (j == bl){
            while (i < al) ret.push_back(a[i++]);
            break;
        }
        if (a[i] < b[j]) ret.push_back(a[i++]);
        else ret.push_back(b[j++]);
    }
}

struct SegTree{
    vector<vector<int>> tree;
    void init(){
        tree.resize(2*n);
        for (int i=0; i<n; ++i) tree[i+n].push_back(arrin[i]);
        for (int i=n-1; i>0; --i) merge(tree[i], tree[i<<1], tree[i<<1|1]);
    }

    ull query(int l, int r, int col){
        ull ret = 0;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1){
            if (l&1) {
                ret += upper_bound(tree[l].begin(), tree[l].end(), col) - tree[l].begin();
                l++;    
            } 
            if (r&1) {
                r--;
                ret += upper_bound(tree[r].begin(), tree[r].end(), col) - tree[r].begin();
            }
        }
        return ret;
    }
}tree;



int main()
{
    cin >> n >> m >> c;
    arr.resize(n); in.resize(n+1); out.resize(n+1); arrin.resize(n);
    g.resize(n+1); vst.resize(n+1,0); vst[1] = 1;
    for (int i=0; i<n;++i) cin >> arr[i];
    for (int i=n-1; i--;){
        int a,b; cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }
    dfs();
    tree.init();
    ull ret = 0;
    ull D = 1000000007;
    while (m--){
        int a,b; cin >> a >> b;
        ret += tree.query(in[a],out[a], b);
        ret %= D;
    }
    cout << ret <<  '\n';

} // namespace std;
