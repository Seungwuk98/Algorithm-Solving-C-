#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

int DIM=11, DM[11], D[12];
vector<ll> arr;
ll ret = 0;
void query(int *qry, int dim, int idx, int nums){
    if (dim == DIM){
        ret += nums&1? arr[idx] : -arr[idx];
        return;
    }

    if (qry[dim]-2 >=0) query(qry, dim+1, idx + (qry[dim]-2)*D[dim+1], nums);
    query(qry, dim+1, idx + (qry[dim+DIM]-1)*D[dim+1], nums+1); 

}

int main()
{
    fastio
    for (int i=0; i<DIM; ++i) cin >> DM[i];
    D[11] = 1;
    for (int i=DIM-1;i>=0; --i) D[i] = D[i+1]*DM[i];
    arr.resize(D[0]);
    for (int i=0; i<D[0]; ++i) cin >> arr[i];
    for (int i=1; i<=DIM; ++i) for (int j=0; j<D[0]; j+=1) {
        if (j%D[i-1]/D[i]) arr[j] += arr[j-D[i]];
    } 

    int Q; cin >> Q;
    int qry[22];
    while (Q--){
        for (int i=0; i<22; ++i) cin >> qry[i];
        ret = 0;
        query(qry, 0, 0, 0);
        cout << ret << '\n';        
    }


  


} // namespace std;
