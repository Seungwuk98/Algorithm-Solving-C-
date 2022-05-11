#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
const ll INF = 1LL<<60;

struct point
{
    ll x, y, xmn, xmx, ymn, ymx;
    int i;
    point(int x, int y) : x(x), y(y) {}
    point() {
        xmn = ymn = INF;
        xmx = ymx = -INF;
    }
    bool operator == (const point &other) const {
        return x == other.x && y == other.y;
    }
    bool operator != (const point &other) const {
        return x != other.x || y != other.y;
    }
    bool operator < (const point &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

bool xcomp(const point &a, const point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool ycomp(const point &a, const point &b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

ll point_to_point(const point &a, const point &b) {
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

int n;
point P[1<<17];
point save[1<<17];
point tree[1<<18];
bool ext[1<<18];
inline ll sq(ll x) {return x*x;}

#define lx x<<1
#define rx x<<1|1

void make_tree(int i, int j, int dep, int x=1) {
    int mid = i + j >> 1;
    if (dep&1) sort(P+i, P+j+1, ycomp);
    else sort(P+i, P+j+1, xcomp);
    tree[x] = P[mid];
    ext[x] = 1;
    if (i <= mid-1) make_tree(i, mid-1, dep+1, lx);
    if (j >= mid+1) make_tree(mid+1, j, dep+1, rx);
    tree[x].xmn = min({tree[lx].xmn, tree[rx].xmn, tree[x].x});
    tree[x].xmx = max({tree[lx].xmx, tree[rx].xmx, tree[x].x});
    tree[x].ymn = min({tree[lx].ymn, tree[rx].ymn, tree[x].y});
    tree[x].ymx = max({tree[lx].ymx, tree[rx].ymx, tree[x].y});
}

void getans(point &now, int dep, ll &ans, int x=1) {
    if (now != tree[x]) {
        ans = min(ans, point_to_point(now, tree[x]));
    }

    if (dep & 1) {
        if (now.y < tree[x].y) {
            if (ext[lx]) getans(now, dep+1, ans, lx);
            if (ext[rx] && ans > sq(tree[rx].ymn - now.y)) getans(now, dep+1, ans, rx);
        } else {
            if (ext[lx] && ans > sq(now.y - tree[lx].ymx)) getans(now, dep+1, ans, lx);
            if (ext[rx]) getans(now, dep+1, ans, rx);
        }
    } else {
        if (now.x < tree[x].x) {
            if (ext[lx]) getans(now, dep+1, ans, lx);
            if (ext[rx] && ans > sq(tree[rx].xmn - now.x)) getans(now, dep+1, ans, rx);
        } else {
            if (ext[lx] && ans > sq(now.x - tree[lx].xmx)) getans(now, dep+1, ans, lx);
            if (ext[rx]) getans(now, dep+1, ans, rx);
        }
    }
}


int main()
{
    int T; cin >> T;
    while (T--){
        memset(ext, 0, sizeof(ext));
        cin >> n;
        vector<point> tmp;
        for (int i=0; i<n; ++i) {
            point w;
            cin >> w.x >> w.y;
            w.i = i;
            tmp.push_back(w);
            save[i] = w;
        } 
        sort(tmp.begin(), tmp.end(), xcomp);
        vector<point> tmp2;
        P[0] = tmp[0];
        int t = 1;
        for (int i=1; i<n; i++) {
            if (tmp[i] != tmp[i-1]) P[t++] = tmp[i];
            else tmp2.push_back(tmp[i]);
        }
        make_tree(0, t-1, 0);
        for (int i=0; i<n; ++i) {
            if (!tmp2.empty() && *lower_bound(tmp2.begin(), tmp2.end(), save[i]) == save[i]) {
                cout << 0 << '\n';
            } else {
                ll ret = INF;
                getans(P[i], 0, ret);
                cout << ret << '\n';
            }
        }
    }
} // namespace std;