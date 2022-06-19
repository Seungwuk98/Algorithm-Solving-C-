#include <bits/stdc++.h>

using namespace std;

int main()
{
    int A[100][100];
    int B[100][100];
    int n,m,k;
    cin >> n >> m;
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) cin >> A[i][j];
    cin >> m >> k;
    for (int i=0; i<m; ++i) for (int j=0; j<k; ++j) cin >> B[i][j];
    int C[100][100] = {0,};
    for (int i=0; i<n; ++i) for (int j=0; j<k; ++j) for (int u=0; u<m; ++u) {
        C[i][j] += A[i][u] * B[u][j];
    }
    for (int i=0; i<n; ++i) {
        for (int j=0; j<k; ++j) cout << C[i][j] << ' ';
        cout << '\n'; 
    } 
} // namespace std;
