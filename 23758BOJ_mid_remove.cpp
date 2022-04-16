#include <bits/stdc++.h>
#include <functional>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastio
    priority_queue<int, vector<int>, less<int>> pq;
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        int x; cin >> x; pq.push(x);
    }
    for (int i=0; i<(n>>1); ++i) pq.pop();
    int ret = 0;
    int cnt = 0;
    int mid = pq.top() >> 1;
    while (mid){
        while (!pq.empty() && pq.top() > mid) {
            pq.pop(); cnt++;
        }
        ret += cnt;
        mid >>= 1;
    }
    cout << ret;
} // namespace name
