#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()

using namespace std;

int n;
R rac[202020];
int xset[404040];
int yset[404040];
int yline[202020];

struct Node{
    Node *l, *r;
    int sum, lazy;
    Node() {
        sum = 0;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;s
    }
};

struct Segtree
{
    Node *root;

    void prop(Node *x, int s, int e){

    }

    void update(int l, int r, Node *x, int s=0, int e=2*n) {
        prop(x,s,e);
        if (e < l || r < s) return;
        if (l <= s && e <= r) {
            
        }
    }

};

struct R{
    int x1, y1, x2, y2;
};

int main()
{
    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> rac[i].x1 >> rac[i].y1 >> rac[i].x2 >> rac[i].y2;
        xset[i<<1] = rac[i].x1; xset[i<<1|1] = rac[i].x2;
        yset[i<<1] = rac[i].y1; yset[i<<1|1] = rac[i].y2;
    }
    sort(xset, xset+2*n);
    sort(yset, yset+2*n);
    for (int i=0; i<n; ++i) {
        rac[i].x1 = lower_bound(xset, xset+2*n, rac[i].x1);
        rac[i].x2 = lower_bound(xset, xset+2*n, rac[i].x2);
        rac[i].y1 = lower_bound(yset, yset+2*n, rac[i].y1);
        rac[i].y2 = lower_bound(yset, yset+2*n, rac[i].y2);

    }



} // namespace std;
