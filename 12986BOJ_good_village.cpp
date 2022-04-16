#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

vector<int> arr, sv, sv_sq, now;
int n, q, sn;
const int INF = 200001;

struct Node
{
    int l, r, idx;
    bool operator<(const Node &t) const{
        if (l/sn != t.l/sn) return l/sn < t.l/sn;
        return r < t.r;
    }
};

void insert(int x){
    int y = arr[x];
    sv[now[y]]--; sv_sq[now[y]/sn]--;
    now[y] ++;
    sv[now[y]]++; sv_sq[now[y]/sn]++; 
}

void remove(int x){
    int y = arr[x];
    sv[now[y]]--; sv_sq[now[y]/sn]--;
    now[y]--;
    sv[now[y]]++; sv_sq[now[y]/sn]++;
}

int find_max(){
    int i=sn;
    for (;i>=0;--i){
        if (sv_sq[i]) break;
    }
    int k=min(n, (i+1)*sn);
    for (int j=n; j>=0; --j){
        if (sv[j]) return j;
    }
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    sn = int(sqrt(n))+1;
    arr.resize(n); sv.resize(n+1); sv_sq.resize(sn+1); now.resize(INF);
    sv[0] = n; sv_sq[0] = n;
    for (int i=0; i<n; ++i){
        int x; cin >> x; x+=INF;
        arr[i] = x;
    }
    vector<Node> qry(q); 
    for (int i=0; i<q; ++i){
        int l, r; cin >> l >> r;
        qry[i] = Node{--l,--r,i};
    }
    sort(qry.begin(), qry.end());
    vector<int> result(q);
    Node pr = qry[0];
    for (int i=pr.l; i<=pr.r; ++i) insert(i);
    result[pr.idx] = find_max();
    for (int w=1; w<q; w++){
        Node nw = qry[w];
        if (pr.l/sn == nw.l/sn){
            for (int x=pr.r+1; x<=nw.r; ++x) insert(x);
            if (pr.l < nw.l){
                for (int x=pr.l; x<nw.l; ++x) remove(x);
            } else {
                for (int x=nw.l; x<pr.l; ++x) insert(x);
            }
        } else{
            if (pr.r < nw.r){
                for (int x=pr.r+1; x<=nw.r; ++x) insert(x);
            } else {
                for (int x=nw.r+1; x<=pr.r; ++x) remove(x);
            }
            for (int x=pr.l; x<nw.l; ++x) remove(x);
        }
        result[nw.idx] = find_max();
        pr = nw;
    }
    for (auto &x : result) cout << x << '\n';



}