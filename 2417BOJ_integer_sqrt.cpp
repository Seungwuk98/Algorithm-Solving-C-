#include <bits/stdc++.h>

using namespace std;
using ll = unsigned long long;
int main(){
    ll n; cin >> n;
    ll lo = 0, hi = 1LLU<<32;
    while (lo < hi){
        ll mid = lo + hi >> 1;
        if (mid*mid < n) lo = mid+1;
        else hi = mid;
    }
    cout << lo;

}