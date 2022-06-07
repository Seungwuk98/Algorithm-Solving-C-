#include <bits/stdc++.h>

using namespace std;

vector<int> g[32][2];
vector<int> T[32][2];
bool vst[32][2] = {0,};
int sz[32][2] = {0,};

#define chk(v, i) v!=p && !vst[v][i]

int getSize(int x, int i, int p=-1) {
    sz[x][i] = 1;
    for (int &nxt : g[x][i]) if (chk(nxt, i)) sz[x][i] += getSize(nxt, x);
    return sz[x][i]; 
}

void getCentroid(int x, int i, vector<int> &cent, int S, int p=-1) {
    bool c = 1;
    for (int &nxt : g[x][i]) if (chk(nxt, i) && sz[nxt][i]*2 >= S) {
        c = 0; getCentroid(nxt, cent, S, x);
    }
    if (c || (sz[x][i]-1<<1 == S && cent.size() == 1)) cent.push_back(x);
}

void levelBFS(int dep, vector<int> &llst, vector<int> &rlst, bool &trouble) {
    if (lnxt.size() != rlst.size()) {
        trouble = 1; return;
    }
    vector<int> lnxt, rnxt;
    for (auto now : llst) {
        T[dep][0].push_back(sz[now]);
        for (auto nxt : g[now][0]) {
            if (!vst[nxt][0]) {
                vst[nxt][0] = 1;
                lnxt.push_back(nxt);
            }
        }
    }
    for (auto now : rlst) {
        T[dep][1].push_back(sz[now]);
        for (auto nxt : g[now][1]){
            if (!vst[nxt][1]) {
                vst[nxt][1] = 1;
                rnxt.push_back(nxt);
            }
        }
    }
    if (T[dep][0] != T[dep][1]) {
        trouble = 1; return;
    }
    if (!lnxt.empty() || !rnxt.empty()) (dep+1, lnxt, rnxt, trouble);
}

int main()
{
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i=0; i<=n; ++i) 
    }

} // namespace std
