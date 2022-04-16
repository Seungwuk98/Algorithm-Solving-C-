#include "FenwickTree.h"

int main(){
    vector<ll> arr = {1,2,3,4,5,6,7,8,9,10};
    build(arr);
    cout << query_L_to_R(2,5) << endl;
    update(3,3);
    cout << query_L_to_R(2,5);
}