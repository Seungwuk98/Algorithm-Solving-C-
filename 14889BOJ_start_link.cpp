#include <bits/stdc++.h>

using namespace std;

int mat[20][20];
int n;

vector<vector<int>> comb;
void combination(vector<int> &tar, vector<int> &now, int N, int R, int i) {
    if (now.size() == R) {
        comb.push_back(now); return;
    } 
    if (R-now.size() != N-i) {
        combination(tar, now, N, R, i+1);
    }
    now.push_back(tar[i]);
    combination(tar, now, N, R, i+1);
    now.pop_back();
}

int main() {
    cin >> n;
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) cin >> mat[i][j];

    vector<int> tar(n);
    for (int i=0; i<n; ++i) tar[i] = i;

    vector<int> now;
    combination(tar, now, n, n>>1, 0);
    
    


}