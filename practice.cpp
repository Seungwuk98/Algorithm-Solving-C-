#include <bits/stdc++.h>

using namespace std;

int arr[1000];
int n,m;
int solve(){
    int ret = 0;
    for (int i=0; i<n-1; ++i) {
        for (int j=i+1; j<n; ++j) {
            bool c = true;
            for (int k=i+1; k<j; ++k) {
                if (min(arr[i], arr[j]) <= arr[k]) {
                    c = false; break;
                }
            }
            ret += c;
        }
    }
    cout << ret << endl;
}


int main()
{
    cin >> n >> m;
    for (int i=0; i<n; ++i) cin >> arr[i];
    
    int op, x, y;
    while (m--){
        cin >> op;
        if (op == 1){
            cin >> x >> y;
            arr[x-1] = y;
        } else {
            solve();
        }
    }

} // namespace std;

