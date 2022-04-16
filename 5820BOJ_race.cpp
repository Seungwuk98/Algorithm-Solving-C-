#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF 1234234
using namespace std;
using pii = pair<int,int>;


int n, k;
vector<int> sz;
vector<bool> vst;
vector<vector<pii>> g;

int get_size(int v, int p=-1){
    sz[v] = 1;
    for (auto &P : g[v]) if(P.first != p && !vst[P.first]){
        int nxt, w; tie(nxt, w) = P;
        sz[v] += get_size(nxt, v);
    }
    return sz[v];
}

int get_centroid(int v, int p, int S){
    for (auto &P : g[v]) if(P.first != p && !vst[P.first] && sz[P.first]*2>S)
        return get_centroid(P.first, v, S);
    return v;
}

int A[1000001] = {0,};
int ret = INF;
void dfs(int v, int p, int dep, int len, vector<pii> &B){
    if (k < len) return;
    B.push_back(pii(dep, len));
    for (auto &P : g[v]){
        int nxt, w; tie(nxt, w) = P;
        if (nxt == p || vst[nxt]) continue;
        dfs(nxt, v, dep+1, len+w, B);
    }
}

void dnc(int v){
    int cent = get_centroid(v,-1,get_size(v)); 

    vector<pii> B;
    vector<int> reset;
    for (auto &P : g[cent]){
        B.clear();
        int nxt, w; tie(nxt, w) = P;
        if (vst[nxt]) continue;
        dfs(nxt, cent, 1, w, B);
        for (auto &PP : B){
            int d1, d2; tie(d1,d2) = PP;
            ret = min(ret, A[k-d2] + d1);
        }
        for (auto &PP : B){
            int d1, d2; tie(d1, d2) = PP;
            A[d2] = min(A[d2], d1);
            reset.push_back(d2);
        }
    }
    for (int &x : reset) A[x] = INF;
    vst[cent] = 1;
    for (auto &P : g[cent]) if (!vst[P.first]) dnc(P.first);
}

int main()
{
    cin >> n >> k;
    g.resize(n+1); sz.resize(n+1); vst.resize(n+1);
    fill(&A[0], &A[1000001], INF); A[0] = 0;
    for (int i=n-1; i--;){
        int x, y, w; cin >> x >> y >> w;
        g[x].push_back(pii(y,w));
        g[y].push_back(pii(x,w));
    }
    dnc(1);
    if (ret == INF) cout << -1 << '\n';
    else cout << ret << '\n';
} // namespace std;

