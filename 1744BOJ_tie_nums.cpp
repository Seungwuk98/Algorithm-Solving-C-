#include <iostream>
#include <algorithm>
#include <deque>
#include <stack>

using namespace std;
using ll = long long;

int main()
{
    deque<ll> d;
    stack<ll> s;
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        d.push_back(x);
    } 
    sort(d.begin(), d.end());
    ll ret = 0;
    while (!d.empty() && d.front() <= 0) {
        s.push(d.front());
        d.pop_front();
        if (s.size() == 2){
            ll a = s.top(); s.pop();
            ll b = s.top(); s.pop();
            ret += a*b;
        }
    }
    if (!s.empty()) {
        d.push_front(s.top()); s.pop();
    }
    while (!d.empty() && d.back() > 1){
        s.push(d.back());
        d.pop_back();
        if (s.size() == 2){
            ll a = s.top(); s.pop();
            ll b = s.top(); s.pop();
            ret += a*b;
        }
    }
    if (!s.empty()){
        d.push_back(s.top()); s.pop();
    }
    while (!d.empty()) {
        ret += d.front();
        d.pop_front();
    }
    cout << ret << '\n';
    

} // namespace std;
