#include <bits/stdc++.h>
#define INF 1000000
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
string a, b;
int n, m;


void script(int l1, int l2, int r1, int r2){
    if (l1>l2 || r1>r2) return;
    if (l1 == l2) {
        for (int j=r1; j<r2; ++j) cout << "a " << b[j] << '\n';
        return;
    }
    if (r1 == r2){
        for (int j=l1; j<l2; ++j) cout << "d " << a[j] << '\n';
        return;
    }


    int M = r2 - r1;
    vector<int> scp1(M+2), scp2(M+2), prev;
    for (int i=1; i<=M; ++i) scp1[i] = i, scp2[M-i+1] = i;
    int mid = l1 + l2 >> 1;
    for (int i=l1; i<mid; ++i){
        prev = scp1;
        scp1[0] = i - l1 +1;
        for (int j=r1; j<r2; ++j){
            int nj = j - r1 + 1;
            if (a[i] == b[j]) scp1[nj] = prev[nj-1];
            else scp1[nj] = min({scp1[nj-1], prev[nj-1], prev[nj]}) + 1;
        }
        // for (auto x : scp1) cout << x << ' ';
        // cout << endl;
    }
    for (int i=l2-1; i>mid; --i){
        prev = scp2;
        scp2[M+1] = l2-i;
        for (int j=r2-1; j>=r1; --j){
            int nj = j-r1+1;
            if (a[i] == b[j]) scp2[nj] = prev[nj+1];
            else scp2[nj] = min({scp2[nj+1], prev[nj+1], prev[nj]})+1;
        }
        // for (auto x : scp2) cout << x << ' ';
        // cout << endl;
    }
    for (int j=0; j<=M; ++j) scp2[j] = scp2[j+1];
    // for (auto x : scp1) cout << x << ' ';
    // cout << endl;
    // for (auto x : scp2) cout << x << ' ';
    // cout << endl << "--------------" << endl;;

    int mn = INF, jl, jr;
    for (int j=r1-1; j<r2; ++j){
        int nj = j-r1+1; bool c = a[mid] != b[j];
        if (nj && mn > scp1[nj-1] + scp2[nj] + c){
            mn = scp1[nj-1] + scp2[nj] + c; jl = j-1; jr = j;
        }
        if (mn > scp1[nj] + scp2[nj] + 1){
            mn = scp1[nj] + scp2[nj] + 1; jl = jr = j;
        }
    }
    script(l1, mid, r1, jl+1);
    (jl ^ jr) ? a[mid] ^ b[jr] ? (cout << "m " << b[jr]) : (cout << "c " << b[jr]) : (cout << "d " << a[mid]);
    cout << '\n';
    script(mid+1, l2, jr+1, r2);
}

int main()
{
    fastio
    cin >> a >> b;
    n = a.size();
    m = b.size();
    script(0,n,0,m);
} // namespace std;
