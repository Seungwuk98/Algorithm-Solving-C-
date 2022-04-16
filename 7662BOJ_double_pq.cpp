#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()

using namespace std;
using t2 = pair<char, int>;

int tree[4040404];

void update(int z, int s = 0, int e = 1000000, int x = 1){
    if (s == e){
        tree[x] ++;
        return;
    }
    int mid = s + e >> 1;
    if (z <= mid) update(z, s, mid, x<<1);
    else update(z, mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

int kth(int k, int s = 0, int e = 1000000, int x = 1){
    if (s == e) {
        tree[x]--;
        return s;
    } 
    int mid = s + e >> 1;
    int diff = tree[x<<1];
    int ret;
    if (k > diff) ret = kth(k - diff, mid+1, e, x<<1|1);
    else ret = kth(k, s, mid, x<<1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
    return ret;
}



int main()
{
    fastio
    int T; cin >> T;
    while (T--){
        memset(tree, 0, sizeof(tree));
        int k; cin >> k;
        vector<t2> qry(k);
        vector<int> arr;
        for (int i=0; i<k; ++i){
            char x; int y;
            cin >> x >> y;
            if (x == 'I') arr.push_back(y);
            qry[i] = t2(x,y);
        }
        sort(all(arr));
        for (int i=0; i<k; ++i) {
            if (qry[i].first == 'I'){
                update(lower_bound(all(arr), qry[i].second) - arr.begin());
            } else if (tree[1]) {
                kth(qry[i].second==1? tree[1] : 1);
            }
        }
        if (!tree[1]){
            cout << "EMPTY" << '\n';
        } else if (tree[1] == 1) {
            int x = arr[kth(1)];
            cout << x << ' ' << x << '\n';
        } else {
            cout << arr[kth(tree[1])] << ' ' << arr[kth(1)] << '\n';
        }
    }



} // namespace std;
