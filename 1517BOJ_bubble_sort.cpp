#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long;
int n;
ll ret = 0;
int arr[1000000];

vector<int> merge(int s1, int e1, int s2, int e2){
    vector<int> tmp;
    while (s1<=e1 || s2<=e2){
        if (s1>e1) while (s2<=e2) tmp.push_back(arr[s2++]);
        if (s2>e2) while (s1<=e1) tmp.push_back(arr[s1++]);
        if (arr[s1] > arr[s2]) {
            tmp.push_back(arr[s2++]);
            ret += e1-s1+1;
        } else tmp.push_back(arr[s1++]);
    }
    return tmp;

}

void merge_sort(int s, int e){
    if (s==e) return;
    int mid = s + e >> 1;
    merge_sort(s,mid); merge_sort(mid+1,e);
    vector<int> tmp = merge(s, mid, mid+1, e);
    for (int i=s; i<=e; ++i) arr[i] = tmp[i-s];
}

int main()
{  
    fastio
    cin >> n;
    for (int i=0; i<n; ++i) cin >> arr[i];
    merge_sort(0,n-1);
    cout << ret;

} // namespace std;
