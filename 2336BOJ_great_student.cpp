#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()

using namespace std;

struct MST
{
    vector<vector<int>> tree;
    int len;
    MST(){}
    void init(vector<int> &arr) {
        len = arr.size();
        tree.resize(2*len);
        for (int i=0; i<len; ++i) tree[i+len].push_back(arr[i]);
        for (int i=len-1; i>0; --i){
            tree[i].resize(tree[i<<1].size() + tree[i<<1|1].size());
            merge(all(tree[i<<1]), all(tree[i<<1|1]), tree[i].begin());
        }
    }

    int query(int l, int r, int x){
        int ret = 0;
        for (l+=len, r+=len+1; l<r; l>>=1, r>>=1) {
            if (l&1) {
                ret += lower_bound(all(tree[l]), x) - tree[l].begin(); l++;
            }
            if (r&1) {
                r--; ret += lower_bound(all(tree[r]), x) - tree[r].begin();
            }
        }
        return ret;
    }
};


struct Node
{
    int x, y, z;
    bool operator<(const Node &t) const {
        return x < t.x;
    }
};

struct compare
{
    bool operator()(const Node &a, const Node &b){
        return a.y < b.y;
    }
};
vector<Node> arr, arrx, arry;

struct MMST
{
    vector<vector<int>> tree;
    vector<MST> intree;
    int m;
    MMST(){}
    MMST(vector<Node> &arr){
        m = arr.size();
        tree.resize(2*m);
        intree.resize(2*m);
        for (int i=0; i<m; ++i) {
            tree[i+m].push_back(arr[i].y); 
            vector<int> tmp;
            tmp.push_back(arr[i].z);
            intree[i+m].init(tmp);
        } 
        for (int i=m-1; i>0; --i){
            tree[i].resize(tree[i<<1].size() + tree[i<<1|1].size());
            merge(all(tree[i<<1]), all(tree[i<<1|1]), tree[i]);
            vector<int> tmp;
            for (int &y : tree[i]) tmp.push_back(arry[y].z);
            intree[i].init(tmp);
        }
    }

};



int main()
{
    fastio
    int n; cin >> n;
    arr.resize(n);
    for (int i=0; i<n; ++i){
        int x; cin >> x; arr[i].x = x;
    }
    for (int i=0; i<n; ++i){
        int x; cin >> x; arr[i].y = x;
    }
    for (int i=0; i<n; ++i){
        int x; cin >> x; arr[i].z = x;
    }

    arrx = arr;
    arry = arr;
    sort(all(arrx));
    compare cy;
    sort(all(arry), cy);
    MMST(arrx);
    cout << 1 << endl;


} // namespace std;
