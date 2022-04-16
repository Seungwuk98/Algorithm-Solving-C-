#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
int n, m;
vector<string> mat;
int dx[] = {-1,0,1};
int dy[] = {1,1,1};


bool dfs(int x, int y, vector<string> &mp){
    if (y==1) return true;

    int ret = 0;
    for (int i=0; i<3; ++i){
        int nx = x+dx[i], ny = y+dy[i];
        if (0<=nx && nx<n && mp[nx][ny] == '.'){
            mp[nx][ny] = 'x';
            if (dfs(nx,ny,mp)) return true;
            mp[nx][ny] = '.';
        }
    }
    return false;
}


int main()
{
    fastio

    cin >> n >> m;
    mat.resize(n);
    for (int i=0; i<n; ++i) cin >> mat[i];
    int mx = 1000000;
    vector<vector<string>> mp;

    for (int j=0; j<m-1; ++j){
        vector<string> tmp;
        for (int i=0; i<n; ++i){
            string x = "";
            x.push_back(mat[i][j]);
            x.push_back(mat[i][j+1]);
            tmp.push_back(x);
        }
        mp.push_back(tmp);
    }


    for (int j=0; j<m-1; ++j){
        int mn = 0;
        for (int i=0; i<n; ++i){
            if (mp[j][i][0] == 'x') continue;
            mn += dfs(i,0,mp[j]);
        }
        mx = min(mx, mn);
    }


    cout << mx;

} // namespace std;
