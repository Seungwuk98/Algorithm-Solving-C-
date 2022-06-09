#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
int pr[10101];
int rk[10101] = {0,};

struct edge
{
    int w, u, v;
    bool operator<(const edge &o) const {
        return w < o.w;
    }
} ed[101010];

int find(int x) {
    return pr[x] == x ? x : (pr[x] = find(pr[x]));
}

bool uni(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    if (rk[rx] > rk[ry]) pr[ry] = rx;
    else {
        pr[rx] = ry;
        if (rk[rx] == rk[ry]) rk[ry]++;
    }
    return true;
}

int main()
{
    fastio
    int v, e; cin >> v >> e;
    for (int i=1; i<=v; ++i) pr[i] = i;
    for (int i=0; i<e; ++i) {
        cin >> ed[i].u >> ed[i].v >> ed[i].w;
    }
    sort(ed, ed+e);
    ll ret = 0;
    for (int i=0; i<e; ++i) {
        if (uni(ed[i].u, ed[i].v)) ret += ed[i].w;
    }
    cout << ret;
} // namespace std;
