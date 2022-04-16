#include "lazy_segtree_no_struc .h"

int main(){
    N = 10;
    vector<ll> arr = {1,2,3,4,5,6,7,8,9,10};
    build(arr);

    cout << query(2,5) << endl;
    update_range(4,2,3);
    cout << query(2,5) << endl;

}