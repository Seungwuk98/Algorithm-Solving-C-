#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int tree[8080808] = {0,};

void update(int w, int s=1, int e=2000000, int x=1){
    if (s==e) {
        tree[x]++; return;
    }
    int mid = s + e >> 1;
    if (w <= mid) update(w, s, mid, x<<1);
    else update(w, mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

int query(int k, int s=1, int e=2000000, int x=1){
    if (s==e) {
        tree[x]--;
        return s;
    } 
    int mid = s+e>>1;
    int diff = tree[x<<1];
    int ret;
    if (k<=diff) ret = query(k, s, mid, x<<1);
    else ret = query(k-diff, mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
    return ret;
}

int main()
{
    fastio
    int n; cin >> n;
    while (n--){
        int op, x;
        cin >> op >> x;
        if (op == 1){
            update(x);
        } else{
            cout << query(x) << '\n';
        }
    }
} // namespace std;
