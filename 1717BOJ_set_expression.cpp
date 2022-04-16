#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int parent[1010100], rnk[1010100] = {0,};
int n, m;

int find(int x){
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

bool uni(int u, int v){
    int ru = find(u), rv = find(v);
    if (ru == rv) return false;
    if (rnk[ru] < rnk[rv]) parent[ru] = rv;
    else {
        parent[rv] = ru;
        if (rnk[ru] == rnk[rv]) rnk[ru]++;
    }
    return true;
}


int main(){
    fastio
    cin >> n >> m;
    for (int i=0; i<=n; ++i) parent[i] = i;
    while (m--){
        int op,a,b; cin >> op >> a >> b;
        if (op == 0) uni(a,b);
        else cout << (find(a)==find(b)? "YES" : "NO") << '\n';
    }
}
