#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
int arr[101010];
int tree[101010] = {0,};
const int sz = 101010;
int n, sn, m, k;

void update(int i, int z){
    for (; i<sz; i+=i&-i) tree[i]+=z;
}

int query(int l, int r){
    l = l<1? 1 : l;
    r = r>100000? 100000 : r;
    int ret = 0;
    for (; r; r-=r&-r) ret += tree[r];
    for (l--; l; l-=l&-l) ret -= tree[l];
    return ret;

}

int insert_right(int x){
    int y = arr[x];
    update(y, 1);
    return query(y-k, y+k)-1;
}

int insert_left(int x){
    int y = arr[x];
    update(y, 1);
    return query(y-k, y+k)-1;
}

int remove_right(int x){
    int y = arr[x];
    update(y, -1);
    return query(y-k, y+k);
}

int remove_left(int x){
    int y = arr[x];
    update(y, -1);
    return query(y-k, y+k);
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
    cin >> n >> k;
    sn = sqrt(n)+1;
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
    }
    cin >> m;
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
        for (int x = lj+1; x <= nj; ++x) ret += insert_right(x);
        for (int x = lj; x > nj; --x) ret -= remove_right(x);
        for (int x = li; x < ni; ++x) ret -= remove_left(x);
        for (int x = li-1; x >= ni; --x) ret += insert_left(x);
        result[nk] = ret;
        tie(li, lj, lk) = tie(ni, nj, nk);
    }
    for (auto x : result) cout << x << ' ';

}