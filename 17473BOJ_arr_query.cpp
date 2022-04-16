#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF ((1<<20)-1)

using namespace std;
struct Node
{
    int mx, on, off, lazy_and, lazy_or;
    Node(){
        mx = on = off = lazy_or = 0;
        lazy_and = INF;
    }
};

Node tree[808080];
int n,m;

void merge(int x){
    tree[x].mx = max(tree[x<<1].mx, tree[x<<1|1].mx);
    tree[x].on = tree[x<<1].on & tree[x<<1|1].on;
    tree[x].off = tree[x<<1].off & tree[x<<1|1].off;
}

void build(vector<int> &arr, int s=1, int e=n, int x=1){
    if (s==e){
        tree[x].mx = tree[x].on = arr[s-1];
        tree[x].off = ~arr[s-1];
        return;
    }
    int mid = s + e >> 1;
    build(arr, s, mid, x<<1); build(arr, mid+1, e, x<<1|1);
    merge(x);
}

void prop(int x, int s, int e){
    if (!tree[x].lazy_or && tree[x].lazy_and == INF) return;
    tree[x].mx &= tree[x].lazy_and;
    tree[x].on &= tree[x].lazy_and;
    tree[x].off |= ~tree[x].lazy_and;
    tree[x].mx |= tree[x].lazy_or;
    tree[x].on |= tree[x].lazy_or;
    tree[x].off &= ~tree[x].lazy_or;

    if (s^e) {
        tree[x<<1].lazy_and |= tree[x].lazy_or;
        tree[x<<1].lazy_or &=tree[x].lazy_and;
        tree[x<<1|1].lazy_and |= tree[x].lazy_or;
        tree[x<<1|1].lazy_or &= tree[x].lazy_and;

        tree[x<<1].lazy_and &= tree[x].lazy_and;
        tree[x<<1].lazy_or |= tree[x].lazy_or;
        tree[x<<1|1].lazy_and &= tree[x].lazy_and;
        tree[x<<1|1].lazy_or |= tree[x].lazy_or;
    }
    tree[x].lazy_and = INF;
    tree[x].lazy_or = 0;
}

void bt_ad(int z, int l, int r, int s=1, int e=n, int x=1){
    // 꺼야하는 비트가 z
    prop(x,s,e);
    if(e < l || r < s) return;
    // 구간 내에 다 꺼져있는 것들은 앞으로 필요없음
    z &= ~tree[x].off;
    if (l <= s && e <= r){
        // 구간에 들어간다면 겹치는 것만 해당 구간에서 꺼줌
        int val = tree[x].on & z;
        // 겹치는 것은 lazy로 보내서 빼줌
        tree[x].lazy_and = ~val;
        // 전파하고 이미 꺼준 것들은 쳐냄
        prop(x,s,e); z -= val;
        // 더 꺼줄게 없으면 여기서 종료
    }
    if (!z) return;
    int mid = s + e >> 1;
    bt_ad(z, l, r, s, mid, x<<1); bt_ad(z, l, r, mid+1, e, x<<1|1);
    merge(x);
}

void bt_or(int z, int l, int r, int s=1, int e=n, int x=1){
    // 켜줘야하는 비트가 z
    prop(x,s,e);
    if (e < l || r < s) return;
    // 구간 내에 이미 켜져있는 애들은 앞으로 의미가 없음
    z &= ~tree[x].on;
    if (l <= s && e <= r){
        // 구간에 들어간다면 구간 내에서 공통적으로 꺼져있는 것들만 켜줌
        int val = tree[x].off & z;
        // 겹치는 것들은 or lazy로 보냄
        tree[x].lazy_or = val;
        // 전파하고 켜준 애들은 쳐냄
        prop(x,s,e); z -= val;
        // 더 킬게 없으면 여기서 종료
    }
    if (!z) return;
    int mid = s + e >> 1;
    bt_or(z, l, r, s, mid, x<<1); bt_or(z, l, r, mid+1, e, x<<1|1);
    merge(x);
}

int query(int l, int r, int s=1, int e=n, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x].mx;
    int mid = s + e >> 1;
    return max(query(l,r,s,mid,x<<1), query(l,r,mid+1,e,x<<1|1));
}


int main()
{
    fastio
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    build(arr);
    cin >> m;
    while (m--) {
        int op, l, r, x; cin >> op >> l >> r;
        if (op == 1){
            cin >> x;
            bt_ad(~x,l,r);
        } else if (op == 2){
            cin >> x;
            bt_or(x,l,r);
        } else{
            cout << query(l, r) << '\n';
        }
    }
} // namespace std;
