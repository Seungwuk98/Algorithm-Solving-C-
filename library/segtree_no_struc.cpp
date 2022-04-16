#include "segtree_no_struc.h"



int main(){
    N = 10;
    vector<ll> arr = {1,2,3,4,5,6,7,8,9,10};
    build(arr);
    cout << query(1,4) << endl;
    update(2, 3);
    cout << query(1,4) << endl;
}