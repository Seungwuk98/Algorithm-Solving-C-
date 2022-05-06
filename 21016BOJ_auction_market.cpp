#include <bits/stdc++.h>

using namespace std;

const int MAX = 2147483647;
const int MIN = -2147483648;

struct Node
{
    int mx, mn, smx, smn, cnt, lazymx, lazymn, lazycnt, mxcnt, mncnt;
    Node() {
        smx = lazymn = MIN;
        smn = lazymx = MAX;
        mxcnt = mncnt = 1;
        cnt = lazycnt = 0;
    }
    void set(int x) {
        mx = mn = x;
    }
};


Node merge(Node left, Node right){
    Node ret;
    ret.cnt = left.cnt + right.cnt;
    if (left.mx == right.mx) {
        ret.mx = left.mx;
        ret.mxcnt = left.mxcnt + right.mxcnt;
        ret.smx = max(left.smx, right.smx);
    } else if (left.mx > right.mx){
        ret.mx = left.mx;
        ret.mxcnt = left.mxcnt;
        ret.smx = max(left.smx, right.mx);
    } else {
        ret.mx = right.mx;
        ret.mxcnt = right.mxcnt;
        ret.smx = max(right.smx, left.mx);
    }

    if (left.mn == right.mn) {
        ret.mn = left.mn;
        ret.mncnt = left.mncnt + right.mncnt;
        ret.smn = min(left.smn, right.smn);
    } else if (left.mn > right.mn) {
        ret.mn = right.mn;
        ret.mncnt = right.mncnt;
        ret.smn = min(right.smn, left.mn);
    } else {
        ret.mn = left.mn;
        ret.mncnt = left.mncnt;
        ret.smn = min(left.smn, right.mn);
    }
}

Node tree[1<<20];
int arr[1<<19];
int n, m;

void build(int s=1, int e=n, int x=1) {
    if (s == e) {
        tree[x].set(arr[s-1]);
        return;
    }
    int mid = s + e >> 1;
    build(s, mid, x<<1);
    build(mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void prop(int x, int s, int e){
    if (tree[x].lazymn < tree[x].mx) {
        tree[x].mx = tree[x].lazymn;
        tree[x].cnt += tree[x].lazycnt * tree[x].mxcnt;
        if (s ^ e) {
            if (tree[x<<1].lazymn > tree[x].lazymn) {
                tree[x<<1].lazymn = tree[x].lazymn;
                tree[x<<1].lazycnt += tree[x].lazycnt;
            }
            if (tree[x<<1|1].lazymn > tree[x].lazymn) {
                tree[x<<1|1].lazymn = tree[x].lazymn;
                tree[x<<1|1].lazycnt += tree[x].lazycnt;
            }
        }
    } 
    tree[x].lazycnt = 0;
    if (tree[x].lazymx > tree[x].mn) {
        tree[x].mn = tree[x].lazymx;
        tree[x].cnt += tree[x].lazycnt * tree[x].mxcnt;
        if (s ^ e){
            if (tree[x<<1].lazymx < tree[x].lazymx) {
                tree[x<<1].lazymx = tree[x].lazymx;
                tree[x<<1].lazycnt += tree[x].lazycnt;
            }
            if (tree[x<<1|1].lazymx < tree[x].lazymx) {
                tree[x<<1|1].lazymx = tree[x].lazymx;
                tree[x<<1|1].lazycnt += tree[x].lazycnt;
            }
        }
    }
}

void update_min(int z, int l, int r, int s=1, int e=n, int x=1){
    prop(x, s, e);
    if (e < l || r < s || tree[x].mx <= z) return;
    if (l <= s && e <= r && tree[x].smx < z) {
        tree[x].lazymn = z;
        prop(x,s,e); return;
    }
    int mid = s + e >> 1;
    update_min(z, l, r, s, mid, x<<1);
    update_min(z, l, r, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

void update_max(int z, int l, int r, int s=1, int e=n, int x=1){
    prop(x,s,e);
    if (e < l || r < s || tree[x].mn >= z) return;
    if (l <= s && e <= r && tree[x].smn > z) {
        tree[x].lazymx = z;
        tree[x].lazycnt = 1;
        prop(x,s,e); return;
    }
    int mid = s + e >> 1;
    update_max(z, l, r, s, mid, x<<1);
    update_max(z, l, r, mid+1, e, x<<1|1);
    tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}


int query(int l, int r, int s=1, int e=n, int x=1){
    prop(x,s,e);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[x].cnt;
    int mid = s + e >> 1;
    return query(l, r, s, mid, x<<1) + query(l, r, mid+1, e, x<<1|1);
}

int main()
{
    cout << (1<<31)-1 << endl;
} // namespace std;
