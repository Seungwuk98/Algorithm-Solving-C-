#include "norecursive_segtree.h"

int main(){
    N = 10;
    vector<ll> arr = {1,2,3,4,5,6,7,8,9,10};
    build(arr);
    cout << query(0,3) << endl;
    update(1, 3);
    cout << query(0,3) << endl;
}