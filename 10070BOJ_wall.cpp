#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int mx[1<<22] = {0,};
int mn[1<<22] = {0,};
const int HF = 1<<21;
int n, k;


void merge(int x){
    mx[x] = max(mx[x<<1], mx[x<<1|1]);
    mn[x] = min(mn[x<<1], mn[x<<1|1]);
}

void build(){
    for (int i=0; i<n; ++i) mn[i|HF] = 0;
    for (int i=HF-1; i>0; --i) merge(i);
}

void do_min(int x, int v){
    mx[x] = v; mn[x] = min(mn[x], v);
}

void do_max(int x, int v){
    mn[x] = v; mx[x] = max(mx[x], v);
}

void prop(int x, int s, int e){
    if (s ^ e) {
        if (mx[x<<1] > mx[x]) do_min(x<<1, mx[x]);
        if (mx[x<<1|1] > mx[x]) do_min(x<<1|1, mx[x]);
        if (mn[x<<1] < mn[x]) do_max(x<<1, mn[x]);
        if (mn[x<<1|1] < mn[x]) do_max(x<<1|1, mn[x]);
    }
}

void update_min(int z, int l, int r, int s=0, int e=HF-1, int x=1){
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        if (mx[x] > z) {
            do_min(x, z);
            prop(x, s, e);
        }
        return;
    }
    prop(x,s,e);
    int mid = s + e >> 1;
    update_min(z, l, r, s, mid, x<<1);
    update_min(z, l, r, mid+1, e, x<<1|1);
    merge(x);
}

void update_max(int z, int l, int r, int s=0, int e=HF-1, int x=1){
    if (e < l || r < s) return;
    if (l <= s && e <= r){
        if (mn[x] < z) {
            do_max(x, z);
            prop(x, s, e);
        }
        return;
    }
    prop(x,s,e);
    int mid = s + e >> 1;
    update_max(z, l, r, s, mid, x<<1);
    update_max(z, l, r, mid+1, e, x<<1|1);
    merge(x);
}

void push(int s=0, int e=HF-1, int x=1){
    if (s == e) return;
    prop(x,s,e);
    int mid = s + e >> 1;
    push(s, mid, x<<1);
    push(mid+1, e, x<<1|1);
}


int main()
{
    fastio
    cin >> n >> k;
    build();
    int op, l, r, h;
    while (k--) {
        cin >> op >> l >> r >> h;
        if (op == 1) update_max(h, l, r);
        else update_min(h, l, r);
    }
    push();
    for (int i=0; i<n; ++i) cout << mx[i|HF] << ' ';
} // namespace std;
