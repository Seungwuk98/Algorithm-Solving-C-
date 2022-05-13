#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
const ll INF = 5e18;


struct P
{
    ll x, y, xmn, xmx, ymn, ymx;
    int i;
    P() {
        xmn = ymn = INF;
        xmx = ymx = -INF;
    }
    bool operator == (const P &other) const {
        return x == other.x && y == other.y;
    }
    bool operator != (const P &other) const {
        return !operator==(other);
    }
} point[1<<17];

P tree[1<<18];
bool ext[1<<18];
int n;

ll sq(ll x) { return x*x;}
ll dist(const P &a, const P &b) { return sq(b.x-a.x) + sq(b.y-a.y);}
bool xcomp(const P &a, const P &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool ycomp(const P &a, const P &b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

void maketree(int l, int r, int st, int x=1) {
    if (st) sort(point+l, point+r+1, ycomp);
    else sort(point+l, point+r+1, xcomp);
    int mid = l + r >> 1;
    tree[x] = point[mid];
    ext[x] = 1;
    if (l <= mid-1) maketree(l, mid-1, st^1, x<<1);
    if (r >= mid+1) maketree(mid+1, r, st^1, x<<1|1);
    tree[x].xmn = tree[x].xmx = tree[x].x;
    tree[x].ymn = tree[x].ymx = tree[x].y;
    if (ext[x*2]) {
        tree[x].xmn = min(tree[x].xmn, tree[x*2].xmn);
        tree[x].xmx = max(tree[x].xmx, tree[x*2].xmx);
        tree[x].ymn = min(tree[x].ymn, tree[x*2].ymn);
        tree[x].ymx = max(tree[x].ymx, tree[x*2].ymx);
    }
    if (ext[x*2+1]) {
        tree[x].xmn = min(tree[x].xmn, tree[x*2+1].xmn);
        tree[x].xmx = max(tree[x].xmx, tree[x*2+1].xmx);
        tree[x].ymn = min(tree[x].ymn, tree[x*2+1].ymn);
        tree[x].ymx = max(tree[x].ymx, tree[x*2+1].ymx);
    }
}

ll ans[101010];

void getans(P &now, int st, int x=1) {
    if (now!=tree[x]) {
        ll d = dist(now, tree[x]);
        ans[now.i] = min(ans[now.i], d);
        ans[tree[x].i] = min(ans[tree[x].i], d);
    } 
    if (st) {
        if (now.y < tree[x].y) {
            if (ext[x<<1]) getans(now, st^1, x<<1);
            if (ext[x<<1|1] && sq(tree[x<<1|1].ymn - now.y) < ans[now.i]) getans(now, st^1, x<<1|1);
        } else {
            if (ext[x<<1] && sq(tree[x<<1].ymx - now.y) < ans[now.i]) getans(now, st^1, x<<1);
            if (ext[x<<1|1]) getans(now, st^1, x<<1|1);
        }
    } else {
        if (now.x < tree[x].x) {
            if (ext[x<<1]) getans(now, st^1, x<<1);
            if (ext[x<<1|1] && sq(tree[x<<1|1].xmn - now.x) < ans[now.i]) getans(now, st^1, x<<1|1);
        } else {
            if (ext[x<<1] && sq(tree[x<<1].xmx - now.x) < ans[now.i]) getans(now, st^1, x<<1);
            if (ext[x<<1|1]) getans(now, st^1, x<<1|1);
        }
    }
}



int main()
{
    fastio
    int T; cin >> T;
    while (T--) {
        cin >> n;
        memset(ext, 0, sizeof(ext));
        fill(&ans[0], &ans[n], INF);
        for (int i=0; i<n; ++i) {
            cin >> point[i].x >> point[i].y;
            point[i].i = i;
        }
        sort(point, point+n, xcomp);
        int t = 0;
        for (int i=0, j=0; i<n; i=j) {
            while (j<n && point[i]==point[j]) j++;
            if (i+1 == j) swap(point[t++], point[i]);
        }
        maketree(0, t-1, 0);
        for (int i=0; i<t; ++i) {
            getans(point[i], 0);
        }
        for (int i=0; i<n; ++i) cout << (ans[i] == INF ? 0 : ans[i]) << '\n';
    }
} // namespace std;
