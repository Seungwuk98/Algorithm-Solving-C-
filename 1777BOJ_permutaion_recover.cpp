#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;


int tree[1<<18];
const int HF = 1<<17;
int arr[1<<18];
int n;

int kth(int k, int s=0, int e=HF-1, int x=1){
    if (s == e) {
        tree[x]--;
        return s;
    } 
    int mid = s + e >> 1, diff = tree[x<<1];
    int ret;
    if (k <= diff) ret = kth(k, s, mid, x<<1);
    else ret = kth(k-diff, mid+1, e, x<<1|1);
    tree[x] = tree[x<<1] + tree[x<<1|1];
    return ret;
}   

int main()
{
    fastio
    cin >> n;
    for (int i=0; i<n; ++i) cin >> arr[i];

    for (int i=1; i<=n; ++i) tree[i|HF] =1;
    for (int i=HF-1; i; --i) tree[i] = tree[i<<1] + tree[i<<1|1];

    int *ret = new int[n];

    for (int i=n; i; --i) {
        int s = kth(i-arr[i-1])-1;
        ret[s] = i;
    }

    for (int i=0; i<n; ++i) cout << ret[i] << ' ';



    delete[] ret;




} // namespace std;
