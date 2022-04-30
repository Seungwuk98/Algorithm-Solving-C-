#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> counting_sort(vector<int> &arr){
    int *C = new int[2000001];
    for (int i=0; i<arr.size(); ++i) C[arr[i]>=0? arr[i] : 2000001-arr[i]]++;
    for (int i=-999999; i<=1000000; ++i) {
        int x = i >= 0? i : 2000001+i;
        C[x] += C[x ? x-1 : 2000001];
    } 
    vector<int> ret(arr.size());
    for (int i=0; i<arr.size(); ++i) ret[C[arr[i]>=0? arr[i] : 2000001+arr[i]]-1] = arr[i], C[arr[i]>=0? arr[i] : arr[i]+2000001]--;
    delete[] C;
    return ret;
}


int main(){
    fastio
    int n; cin >> n;
    vector<int> p(n);
    for (int i=0; i<n; ++i) cin >> p[i];
    p = counting_sort(p);
    for (int i=0; i<p.size(); ++i) cout << p[i] << '\n';
}