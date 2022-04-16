#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#define LOG 17
#define all(v) v.begin(), v,end()
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define get(i,v) get<i>(v)

using namespace std;
vector<vector<int>> g, pr;
vector<int> dep;
vector<bool> vst;
int n,q;

void dfs(int node = 1){
    for (int next : g[node]) {
        if (!vst[next]){
            vst[next] = 1;
            pr[next][0] = node;
            dep[next] = dep[node] + 1;
            dfs(next); 
        }
    }
}

void parent(){
    for (int i=1; i<LOG; ++i)
        for (int j=1; j<=n; ++j) 
            pr[j][i] = pr[pr[j][i-1]][i-1];
}

int lca(int a, int b){
    if (dep[a] < dep[b]) swap(a,b);
    for (int i=LOG-1; i>=0; --i) if (dep[a] - dep[b] >= (1<<i)) a = pr[a][i];
    for (int i=LOG-1; i>=0; --i) if (pr[a][i] != pr[b][i]) {
        a = pr[a][i]; b = pr[b][i];
    }
    if (a==b) return a;
    return pr[a][0];
}

int dist(int a, int b, int l){
    return dep[a] + dep[b] - 2 * dep[l];
}

int find_parent(int a, int d){
    for (int i = LOG-1; i>=0; --i) if (d >= (1<<i)) {
        a = pr[a][i];
        d -= 1<<i;
    } 
    return a;
}

int main()
{
    fastio
    cin >> n;
    g.resize(n+1); pr.resize(n+1); vst.resize(n+1); dep.resize(n+1);
    for (int i=0; i<=n; ++i) pr[i].resize(LOG);
    for (int i=n-1;i--;){
        int x,y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    vst[1] = 1;
    dfs(); parent();
    cin >> q;
    while (q--){
        int a,b,c; cin >> a >> b >> c;
        int A,B,C;
        int lcaAB = lca(a,b);
        int lcaBC = lca(b,c);
        int lcaCA = lca(c,a);
        if (lcaAB == lcaBC && lcaBC == lcaCA) {
            int l = lcaAB; 
            int distA = dist(a,l,l);
            int distB = dist(b,l,l);
            int distC = dist(c,l,l);
            if (distA == distB) {
                A = a; B = b; C = c;
            } else if (distA == distC){
                A = a; B = c; C = b;
                swap(distB, distC);
            } else if (distB == distC){
                A = b; B = c; C = a;
                swap(distA, distB); swap(distB, distC);
            } else {
                cout << -1 << '\n'; continue;
            }
            
            if ((distA+distC & 1) || distC < distA) cout << -1 << '\n';
            else {
                int dd = distA + distC >> 1;
                C = find_parent(C, dd);
                cout << C << '\n';
            }
            continue;
        }
        else if (lcaAB == lcaBC) {
            A = a; B = c; C = b;
            swap(lcaAB, lcaCA);
            if (dep[A] < dep[B]) swap(A,B);
        } else if (lcaBC == lcaCA) {
            A = a; B = b; C = c;
            if (dep[A] < dep[B]) swap(A,B);
        } else {
            A = b; B = c; C = a;
            swap(lcaAB, lcaBC);
            if (dep[A] < dep[B]) swap(A,B);
        }
        // cout << A << ' ' << B << ' ' << C <<endl;
        int distAB_A = dist(A,lcaAB,lcaAB);
        int distAB_B = dist(B,lcaAB,lcaAB);
        int distAB_C = dist(lcaAB,C,lcaCA);
        int distCA_A = dist(lcaCA,A,lcaCA);
        // cout << distAB_A << ' ' << distAB_B << ' ' << distAB_C << endl;
        if (distAB_A == distAB_B){
            if (distAB_A > distAB_C || (distAB_A + distAB_C & 1)) cout << -1 << '\n';
            int dd = distAB_A + distAB_C >> 1;
            if (dd <= distCA_A) {
                A = find_parent(A, dd);
                cout << A << '\n';
            } else {
                C = find_parent(C, dd);
                cout << C << '\n';
            }
        } else {
            if ((distAB_A+distAB_B & 1) || distAB_A < distAB_C) cout << -1 << '\n';
            int dd = distAB_A + distAB_C >> 1;
            A = find_parent(A, dd);
            int distA_B = dist(A,B,lcaAB);
            if (distA_B == dd) cout << A << '\n';
            else cout << -1 << '\n';
        }

    }

} // namespace std;

