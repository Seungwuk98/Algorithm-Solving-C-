#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
int arr[101010];
int tree[404040] = {0,};
int n, sn, m, sz;

void update(int i, int z){
    tree[i|=sz] += z;
    while (i>>=1) tree[i] = tree[i<<1] + tree[i<<1|1];
}

int query(int l, int r){
    int ret = 0;
    for (l|=sz, r|=sz; l<=r; l>>=1, r>>=1){
        if (l&1) ret += tree[l++];
        if (~r&1) ret += tree[r--];
    }
    return ret;
}

int insert_right(int x){
    int y = arr[x];
    update(y, 1);
    return query(y+1, sz-1);
}

int insert_left(int x){
    int y = arr[x];
    update(y, 1);
    return query(0, y-1);
}

int remove_right(int x){
    int y = arr[x];
    update(y, -1);
    return query(y+1, sz-1);
}

int remove_left(int x){
    int y = arr[x];
    update(y, -1);
    return query(0, y-1);
}

struct qry
{
    int i, j, k;
    bool operator< (const qry &other) const {
        if (i/sn != other.i/sn) return i/sn < other.i/sn;
        return j < other.j;
    }
} Q[101010];



int main(){
    fastio
    cin >> n >> m;
    sn = sqrt(n)+1;
    vector<int> x(n);
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
        x[i] = arr[i];
    }
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    for (sz=1; sz<=x.size(); sz<<=1);
    
    for (int i=0; i<n; ++i) arr[i] = lower_bound(all(x), arr[i]) - x.begin();
    for (int i=0; i<m; ++i) {
        int s, e; cin >> s >> e;
        Q[i] = {s-1, e-1, i};        
    }
    sort(Q, Q+m);

    vector<ll> result(m);
    int li, lj, lk, ni, nj, nk;
    tie(li, lj, lk) = tie(Q[0].i, Q[0].j, Q[0].k);
    ll ret = 0;
    for (int x=li; x<=lj; ++x) ret += insert_right(x); 
    result[lk] = ret;

    for (int w=1; w<m; ++w) {
        tie(ni, nj, nk) = tie(Q[w].i, Q[w].j, Q[w].k);

        if (li/sn == ni/sn) {
            for (int x=lj+1; x<=nj; ++x) ret += insert_right(x);
            if (li < ni) for (int x=li; x<ni; ++x) ret -= remove_left(x); 
            else for (int x=li-1; x>=ni; --x) ret += insert_left(x);
        } else {
            if (lj < nj) for (int x=lj+1; x<=nj; ++x) ret += insert_right(x); 
            else for (int x=lj; x>nj; --x) ret -= remove_right(x);
            for (int x=li; x<ni; ++x) ret -= remove_left(x);
        }
        result[nk] = ret;
        tie(li, lj, lk) = tie(ni, nj, nk);
    }
    for (auto x : result) cout << x << ' ';

}