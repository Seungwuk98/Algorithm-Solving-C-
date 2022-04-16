#include <iostream>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    crope rp;
    while (T--){
        string s;
        cin >> s;
        rp.clear();
        rp.append(s.c_str());
        while (1) {
            string x, y; int z, w;
            cin >> x; if (x=="END") break;
            if (x == "I") {
                cin >> y >> z;
                crope tmp(y.c_str());
                rp = rp.substr(0,z) + tmp + rp.substr(z,rp.size());
            } else if(x == "P"){
                cin >> z >> w;
                cout << rp.substr(z,w-z+1) << '\n';
            }
        }
    }    
    
}