#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <functional>
#define INF 9223372036854775808LLU
#define all(v) v.begin(), v,end()
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define get(i,v) get<i>(v)

using namespace std;
using ll = unsigned long long;
using t5 = tuple<int, int, int, int, int>;
using t3 = tuple<ll, int, int>;
using vll = vector<vector<ll>>;
vll mat;
vector<t5> qry;
vector<ll> result;
int n,m,q;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
ll from_home[5][5][100000];

void solve(vector<t5> &qry, int l, int r){
    if (l > r) return;
    int mid = l + r >> 1;
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) for (int k=l; k<=r; ++k) from_home[i][j][k] = INF;
    for (int i=0; i<n; ++i){
        priority_queue<t3, vector<t3>, greater<t3>> pq;
        from_home[i][i][mid] = mat[i][mid];        
        pq.emplace(t3(mat[i][mid], i, mid));
        while (!pq.empty()){
            ll x,y,v; tie(v,x,y) = pq.top(); pq.pop();
            for (int j=0; j<4; ++j){
                int nx = x + dx[j], ny = y + dy[j];
                if (ny < l || ny > r || nx < 0 || nx >= n) continue;
                ll from_start = mat[nx][ny] + v; 
                if (from_start < from_home[i][nx][ny]){
                    from_home[i][nx][ny] = from_start;
                    pq.emplace(t3(from_start, nx, ny));
                }
            }
        }
    }
    vector<t5> left, right;
    for (auto &t : qry){
        int x1, y1, x2, y2, k;
        tie(x1, y1, x2, y2, k) = t;
        for (int i=0; i<n; ++i){
            result[k] = min(result[k], from_home[i][x1][y1] + from_home[i][x2][y2] - mat[i][mid]);
        }
        if (y1 < mid && y2 < mid) left.emplace_back(t);
        else if (y1 > mid && y2 > mid) right.emplace_back(t);
    }

    solve(left, l, mid-1);
    solve(right, mid+1, r);
}


int main(){
    fastio
    cin >> n >> m;
    mat.resize(n);
    for (int i=0; i<n; ++i) {
        mat[i].resize(m);
        for (int j=0; j<m; ++j) cin >> mat[i][j];
    }
    cin >> q;
    result.resize(q, INF);
    for (int i=0; i<q; ++i) {
        int x,y,z,w; cin >> x >> y >> z >> w;
        qry.push_back(t5(--x,--y,--z,--w,i));
    }
    solve(qry, 0, m-1);
    for (ll x : result) cout << x <<'\n';
}