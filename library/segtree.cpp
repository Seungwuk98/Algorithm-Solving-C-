#include "segtree1.h"


int main(){
    vector<ll> arr(256);
    for (int i=0; i<256; ++i) arr[i] = i+1;
    Segtree tree = Segtree(arr);
    cout << tree.query(tree.tree, 2, 5) << endl;
    tree.update(tree.tree, 3, 2);
    cout << tree.query(tree.tree, 2, 5) << endl;
}