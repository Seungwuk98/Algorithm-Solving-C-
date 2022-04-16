#include <iostream>
#include <vector>
#include <algorithm>   

using namespace std;
using ull = unsigned long long;

vector<int> v;

int main()
{
    int n; cin >> n;
    while (n--){
        int x; cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    cout << (ull)v.front()*v.back();
} // namespace std;
