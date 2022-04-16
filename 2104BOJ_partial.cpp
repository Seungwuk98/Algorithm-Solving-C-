#include <bits/stdc++.h>

using ll = long long;
using namespace std;
struct Node
{
    ll sm, mn, ret;
    Node(){
        sm = 0;
    }
    Node(int x){
        sm = mn = x;
        ret = x*x;
    }
};

Node tree[1<<18];
const int sz = 1<<17;
int n;

Node merge(Node &A, Node &B){
    Node ret;
    ret.mn = min(A.mn, B.mn);
    ret.sm = A.sm + B.sm;
    ret.ret = ret.mn * ret.sm; 
    return ret;
}

void build(vector<int> &arr){
    for (int i=0; i<n; ++i) tree[i|sz] = Node(arr[i]);
    for (int i=sz-1; i; --i) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}


int main()
{
    cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    build(arr);
    ll ret = 0;
    for (int l=sz, r=sz+n-1; l<=r; l>>=1, r>>=1){
        if (l&1) ret = max(ret, tree[l++].ret);
        if (~r&1) ret = max(ret, tree[r--].ret);
    }
    cout << ret;

} // namespace std;
