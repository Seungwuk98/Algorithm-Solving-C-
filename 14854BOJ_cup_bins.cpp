#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int n, m;
int arr[101010];
int tmp[101010];
int tree[404040];
int lazy[404040] = {0,};
pair<int,int> qry[101010];


void merge(int x){
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

void buildSeg(int s=1, int e=n, int x=1){
    lazy[x] = -1;
    if (s==e) {
        tree[x] = tmp[s-1];
        return;
    } 
    int mid = s + e >> 1;
    buildSeg(s, mid, x<<1); buildSeg(mid+1, e, x<<1|1);
    merge(x);
}

void build(int x){
    for (int i=0; i<n; ++i){
        tmp[i] = arr[i]>x;
    }
    buildSeg();
}
void prop(int x, int s, int e){
    if (lazy[x] == -1) return;
    tree[x] = lazy[x] * (e-s+1);
    if (s^e) lazy[x<<1] = lazy[x<<1|1] = lazy[x];
    lazy[x] = -1;
}


void update(int d, int l, int r, int s=1, int e=n, int x=1) {
    prop(x, s, e);
    if (s > e || e < l || r < s) return;
    if (l <= s && e <= r) {
        lazy[x] = d; prop(x, s, e);
        return;
    }
    int mid = s + e >> 1;
    update(d, l, r, s, mid, x<<1); update(d, l, r, mid+1, e, x<<1|1);
    merge(x);
}

int find(int i, int s=1, int e=n, int x=1){
    prop(x, s, e);
    if (s==e) return tree[x];
    int mid = s+e>>1;
    if (i <= mid) return find(i, s, mid, x<<1);
    return find(i, mid+1, e, x<<1|1);
}

int interval(int l, int r, int s=1, int e=n, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x];
    int mid = s + e >> 1;
    return interval(l, r, s, mid, x<<1) + interval(l, r, mid+1, e, x<<1|1);
}

int query(int mid){
    build(mid);
    for (int i=0; i<m; ++i){
        int l, r; tie(l,r) = qry[i];
        int d = 1;
        if (l>=r) swap(l,r), d = -1;
        int one = interval(l, r);
        int zero = r-l+1-one;
        if (d == 1){
            update(0, l, l+zero-1);
            update(1, l+zero, r);
        } else {
            update(1, l, l+one-1);
            update(0, l+one, r);
        }
    }
    return find(n+1>>1);
}

int main()
{
    fastio
    cin >> n >> m;
    for (int i=0; i<n; ++i) cin >> arr[i];
    for (int i=0; i<m; ++i) {
        int x, y; cin >> x >> y;
        qry[i] = {x,y};
    }
    int lo=1, hi=n;
    while (lo < hi){
        int mid = lo + hi >> 1;
        if (query(mid)) lo = mid+1;
        else hi = mid; 
    }
    cout << lo;
} // namespace std;
