#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using t4 = tuple<int,int,int,int>;


bool mat[1001][1001];
int vst[1001][1001]={0,};
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int n,m,k;
bool valid_coord(int x, int y){
    return 0<=x && x<n && 0<=y && y<m;
}

int main()
{
    fastio
    cin >> n >> m >> k;
    vst[0][0]=~0;
    for (int i=0; i<n; ++i){
        string s; cin >> s;
        for (int j=0; j<m; ++j) mat[i][j] = s[j]=='1'? 1 : 0;
    }
    queue<t4> q = queue<t4>();
    bool s = 1;
    q.push({0,0,0,1});
    while (!q.empty()){
        int l = q.size();
        for (int i=0; i<l; ++i){
            int x,y,w,c;
            tie(x,y,w,c) = q.front(); q.pop();
            if (x==n-1 && y==m-1){
                cout << c; return 0;
            }
            for (int i=0; i<4; ++i){
                int nx = x+dx[i], ny = y+dy[i];
                if (!valid_coord(nx,ny)) continue;
                if (~vst[nx][ny] & (1<<w)){
                    if (mat[nx][ny]){
                        if (w < k){
                            if (s) {
                                vst[nx][ny] = ~((1<<w)-1);
                                q.push({nx,ny,w+1,c+1});
                            } 
                            else{
                                q.push({x,y,w,c+1});
                            }
                        }
                    } else{
                        vst[nx][ny] = ~((1<<w)-1);
                        q.push({nx,ny,w,c+1});
                    }
                }
            }
        }
        s ^=1;
    }
    cout << -1;
} // namespace std;
