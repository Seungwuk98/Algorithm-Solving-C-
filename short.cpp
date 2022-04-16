#include <bits/stdc++.h>
using namespace std;
using l = long long;

int I=11, M[11], D[12];
vector<l>a;
l ret = 0;
void query(int *q, int d, int i, int n){
    if (d == I){ret += n&1? a[i] : -a[i];return;}
    if (q[d]-2 >=0) query(q, d+1, i + (q[d]-2)*D[d+1], n);
    query(q, d+1, i + (q[d+I]-1)*D[d+1], n+1); 
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i=0; i<I; ++i) cin >> M[i];
    D[I] = 1;
    for (int i=I-1;i>=0; --i) D[i] = D[i+1]*M[i];
    a.resize(D[0]);
    for (int i=0; i<D[0]; ++i) cin >> a[i];
    for (int i=1; i<=I; ++i) for (int j=0; j<D[0]; j+=1) if (j%D[i-1]/D[i]) a[j] += a[j-D[i]];

    int Q; cin >> Q;
    int q[22];
    while (Q--){ for (int i=0; i<22; ++i) cin >> q[i]; ret = 0; query(q, 0, 0, 0);cout << ret << '\n';}
}
