#include <iostream>
#include <queue>
#include <vector>

using ll = long long;
using namespace std;

int n;
vector<ll> arr;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    queue<int> q;
    while (!q.empty())
        q.pop();
    for (int i = 0; i < n; ++i)
    {
        ll x;
        cin >> x;
        arr.push_back(x);

        if (arr[i] < 0)
            q.push(i);
    }
    ll cnt = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        if (arr[now] >= 0)
            continue;
        ll x = arr[now];
        arr[now] = -x;
        arr[(now + 1) % n] += x;
        arr[(now + n- 1) % n] += x;
        if (arr[(now + 1) % n] < 0)
            q.push((now + 1) % n);
        if (arr[(now +n - 1) % n] < 0)
            q.push((now +n - 1) % n);
        cnt++;
    }
    cout << cnt << endl;

} // namespace std;
