#include <iostream>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

int n,m,q;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s; 
    cin >> m >> s >> q; 
    n = s.size();
    crope rp;
    rp.append(s.c_str());
    while (q--){
        int l, r, x; cin >> l >> r >> x;
        rp = rp.substr(0,x) + rp.substr(l,r-l) + rp.substr(x,rp.size());
        if (rp.size() > m) rp = rp.substr(0,m);
    }
    cout << rp;

    
}