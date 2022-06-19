#include <bits/stdc++.h>

using namespace std;


void pstar(int n) {
    while (n--) cout << '*';
}

void pspace(int n){
    while (n--) cout << ' ';
}

int main()
{
    int n; cin >> n;
    int m = 2*n-1;
    int t = m;
    int u = 0;
    while (t--) {
        pspace(u);
        pstar(abs(m));
        m-=2;
        if (m==-1) m-=2;
        if (m < -1) u--;
        else u++;
        cout << '\n';
    }

} // namespace std;
