#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int idx[1<<18];
int mn[1<<18];
int sz = 1<<17;

void merge(int x){
    if (mn[x<<1] <= mn[x<<1|1]){
        mn[x] = mn[x<<1];
        idx[x] = idx[x<<1];
    } else {
        mn[x] = mn[x<<1|1];
        idx[x] = idx[x<<1|1];
    }
}

int main(){
    fastio
    int n; cin >> n;
    fill(&mn[0], &mn[1<<18], 1<<30);
    for (int i=0; i<n; ++i) {
        cin >> mn[i|sz]; idx[i|sz] = i+1;
    }
    for (int i=sz-1; i; --i) merge(i);
    int m; cin >> m;
    while (m--){
        int op, i, v; cin >> op;
        if (op == 1){
            cin >> i >> v;
            mn[--i|=sz] = v;
            while (i>>=1) merge(i);
        } else {
            cout << idx[1] << '\n';
        }
    }






}