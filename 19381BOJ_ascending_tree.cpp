#include <bits/stdc++.h>

using namespace std;

vector<int> child[101010];
int pr[101010] = {0,};
int arr[101010] = {0,};
int n;


int main()
{
    cin >> n >> arr[1];
    for (int i=2; i<=n; ++i) {
        cin >> pr[i] >> arr[i];
        child[pr[i]].push_back(i);
    }
    


} // namespace std;


