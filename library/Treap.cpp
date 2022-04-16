#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;
const int A = 1664525;
const int B = 1013904223;
const ll M = 1LL<<32;
ll X = 1015568748; 

int ran(){
    return X = (A*X + B) % M;
}


struct Node
{
    Node *l, *r;
    int cnt, pty, val;
    ll sum;
    Node(int x) {
        l = r = nullptr;
        sum = 0; cnt = 1; val = x;
        pty = ran();
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};

struct Treap{
    using pnn = pair<Node*, Node*>;
    Node *tree;
    
    void split(Node *x, Node *&left, Node *&right, int k) {
        if (!x) {
            left = right = nullptr;
            return;
        } 
        if (k <= x->val){
            split(x->l, left, x->l, k);
            right = x;
        } else {
            split(x->r, x->r, right, k);
            left = x;
        }
        update(x);
    }

    void update(Node *x){
        x->cnt = 1;
        if (x->l){
            x->cnt += x->l->cnt;
        }
        if (x->r){
            x->cnt += x->r->cnt;
        }
    }

    void insert(Node *&root, Node *x){
        if (!root) {
            root = x;
            return;
        }
        if (root->pty < x->pty){
            
        }

    }

    int& operator[](int k){
        Node *x = tree;
        while (1){
            while (x->l && x->l->cnt > k) x=x->l;
            if (x->l) k -= x->l->cnt;
            if (!k--) return x->val;
            x = x->r;
        }
    }

} treap;



int main()
{
    fastio
    int n; cin >> n;
    int x; 
    for (int i=0; i<n; ++i){
        cin >> x;
        cout << treap[i>>1] << '\n';
    }

} // namespace std;
