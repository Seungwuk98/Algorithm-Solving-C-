#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int mat[50][50];

int main()
{
    int T; cin >> T;

    while (T--) {
        int n,m; cin >> n >> m;
        mat[0][0] = 1;
        mat[0][1] = 0;
        for (int i=2; i<m; ++i) {
            mat[0][i] = mat[0][i-1] == mat[0][i-2] ? mat[0][i-3] : mat[0][i-1];
        }
        for (int i=0; i<m; ++i) mat[1][i] = mat[0][i]^1;
        for (int j=0; j<m; ++j) for (int i=2; i<n; ++i) {
            mat[i][j] = mat[i-1][j] == mat[i-2][j] ? mat[i-3][j] : mat[i-1][j];
        }

        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) cout << mat[i][j] << ' ';
            cout << '\n';
        }
    }
} // namespace std;
