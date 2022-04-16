#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
struct Node
{
    int bit, lazy;
    Node(){
        bit = 1;
        lazy = 0;
    }
};

Node tree[404040];

void prop(int x, int s, int e){
    if (!tree[x].lazy) return;
    tree[x].bit = tree[x].lazy;
    if (s^e){
        tree[x<<1].lazy = tree[x].lazy;
        tree[x<<1|1].lazy = tree[x].lazy;
    }
    tree[x].lazy = 0;
}

void update(int l, int r, int s, int e, int k, int x = 1){
    prop(x,s,e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        tree[x].lazy = 1<<(k-1);
        prop(x,s,e); return;
    }
    int mid = s + e >> 1;
    update(l, r, s, mid, k, x<<1); update(l, r, mid+1, e, k, x<<1|1);
    tree[x].bit = tree[x<<1].bit | tree[x<<1|1].bit;
}

int query(int l, int r, int s, int e, int x = 1){
    prop(x, s, e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x].bit;
    int mid = s+e>>1;
    return query(l, r, s, mid, x<<1) | query(l, r, mid+1, e, x<<1|1); 
}

int main()
{
    fastio
    int n,T,Q; cin >> n >> T >> Q;
    while (Q--){
        char op; int x,y,z; cin >> op >> x >> y;
        if (x > y) swap(x,y);
        if (op == 'C'){
            cin >> z;
            update(x,y,1,n,z);
        } else{
            int bit = query(x,y,1,n);
            int ret = 0;
            for (int i=T; i--;){
                ret += bit&1;
                bit>>=1;
            }
            cout << ret << '\n';
        }
    }
} // namespace std;
