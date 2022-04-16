#include <bits/stdc++.h>
using namespace std;
#define X first;
#define Y second;

int board[505][505];
bool vis[505][505];
int n, m;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int ans = 0;
	int num_pic = 0;
	queue<pair<int, int>> Q;

	cin >> n >> m; // m, n 아님?
    fill(&vis[0][0], &vis[n-1][m], 0);
	// 도화지 채우기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> board[i][j];
	}
	
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) cout << board[i][j] << ' ';
        cout << endl;
    }

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 1 && vis[i][j] != 1) {

				int largest_2 = 0;
				num_pic++;
				vis[i][j] = 1;
				Q.push({ i,j });

				while (!Q.empty()) {
					largest_2++;
					auto cur = Q.front(); Q.pop();
                    cout << cur.first << ' ' << cur.second << endl;
					for (int dir = 0; dir < 4; dir++) {
						int nx = cur.first + dx[dir];
						int ny = cur.second + dy[dir];
						if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
						if (vis[nx][ny] || board[nx][ny] != 1) continue;
						vis[nx][ny] = 1;
						Q.push({ nx,ny });					
					}
				}
				ans = max(ans, largest_2);
			}
		}
	}
	cout << num_pic << "\n" << ans;
}