#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int n,m;


struct segtree
{
    int tree[1<<18];
    static const int HF = 1<<17;

    void update(int i, int z){
        tree[i|=HF]+=z;
        while (i>>=1) tree[i] = tree[i<<1] + tree[i<<1|1];
    }

    ll query(int l, int r) {
        ll ret = 0;
        for (l|=HF, r|=HF; l<=r; l>>=1, r>>=1){
            if (l&1) ret += tree[l++];
            if (~r&1) ret += tree[r--];
        }
        return ret;
    }
} t1, t2;



int main()
{
    
} // namespace std;
