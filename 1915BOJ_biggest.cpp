#include <iostream>
#include <string>
#include <memory.h>
using namespace std;
const int maxNum = 1001;
int n, m;
int Map[maxNum][maxNum];
int dp[maxNum][maxNum];
//dp[i][j] i,j에 일때 가능한 가장 긴 정사각형의 길이
int solve(int i, int j)
{
	if (i <= 0 || j <= 0) return 0;
	
	int& ret = dp[i][j];
	if (ret != -1) return ret;
    if (!Map[i][j]){
        solve(i,j-1); solve(i-1,j); solve(i-1,j-1);
        return ret = 0;
    }
	ret = min(solve(i, j -1), min(solve(i - 1, j), solve(i - 1, j - 1))) + 1;
	return ret;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		string str; cin >> str;
		for (int j = 0; j < str.size(); j++)
		{
			int num = str[j] - '0';
			Map[i][j + 1] = num;
		}
	}
	memset(dp, -1, sizeof(dp));
	solve(n, m);
	int Ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			Ans = max(Ans, dp[i][j]);
		}
	}
	cout << Ans * Ans;
	return 0;
}