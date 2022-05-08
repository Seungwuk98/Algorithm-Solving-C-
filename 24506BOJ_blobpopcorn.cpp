#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

int mx[1<<18];
int mn[1<<18];
int lisl[1<<18];
int lisr[1<<18];
int n, m;
#define parameter int s=1, int e=n, int x=1
#define lx (x<<1)
#define rx (x<<1|1)


int leftlis(int z, int x, int s, int e){
    if (z < mn[x]) return lisl[x];
    if (mx[x] < z) return 0;
    if (s == e) return 0;
    int mid = s + e >> 1;
    return leftlis(z, lx, s, mid) + leftlis(max(mx[lx], z), rx, mid+1, e);
}

int rightlis(int z, int x, int s, int e){
    if (z < mn[x]) return lisr[x];
    if (mx[x] < z) return 0;
    if (s == e) return 0;
    int mid = s + e >> 1;
    return rightlis(z, rx, mid+1, e) + rightlis(max(mx[rx], z), lx, s, mid);
}
void merge(int x, int s, int e){
    mx[x] = max(mx[lx], mx[rx]);
    mn[x] = min(mn[lx], mn[rx]);
    int mid = s + e >> 1;
    lisl[x] = lisl[lx] + leftlis(mx[lx], rx, mid+1, e);
    lisr[x] = lisr[rx] + rightlis(mx[rx], lx, s, mid);
}


void build(parameter){
    if (s == e) {
        cin >> mx[x];
        mn[x] = mx[x];
        lisl[x] = lisr[x] = 1;
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, lx); build(mid+1, e, rx);
    merge(x, s, e);
}

void update(int i, int v, parameter){
    if (s == e) {
        mn[x] = mx[x] = v;
        return;
    }
    int mid = s + e >> 1;
    if (i <= mid) update(i, v, s, mid, lx);
    else update(i, v, mid+1, e, rx);
    merge(x, s, e);
}


int main()
{
    fastio
    cin >> n >> m;   
    build();
    int op, x, y;
    while (m--){
        cin >> op;
        if (op == 1) {
            cin >> x >> y;
            update(x, y);
        } else {
            cout << (2*n - lisl[1] - lisr[1]) << '\n';
        }
    }
} // namespace std;
