#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    int h;
    string val;
    Node *l, *r, *p;
    Node(){
        val = "";
        h = 1;
        l = r = p = nullptr;
    }
    Node(string val) : val(val){
        h = 1;
        l = r = p = nullptr;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
};


struct AVLTree
{
    Node *root;
    int size;
    AVLTree(){
        root = nullptr;
        size = 0;
    }
    ~AVLTree(){
        if (root) delete root;
    }

    void update(Node *x){
        x->h = 1;
        if (x->l) x->h = max(x->h, x->l->h+1);
        if (x->r) x->h = max(x->h, x->r->h+1);
    }

     void rotate(Node *x){
        Node *p = x->p;
        Node *a;
        if (p->l == x){
            p->l = a = x->r;
            x->r = p;
        } else{
            p->r = a = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (a) a->p = p;
        (x->p ? x->p->l == p ? x->p->l : x->p->r : root) = x;
        update(p);
        update(x);
    }

    Node* rotate(Node *x, Node *p, Node *g){
        if ((p->l==x) != (g->l==p)) {
            rotate(x); rotate(x);
            return x;
        } else{
            rotate(p);
            return p;
        }
    }

    void rebalance(Node *x){
        update(x);
        Node *p = x->p, *g;
        if (!p || !p->p) return;
        update(p);
        g = p->p;
        while (g){
            update(g);
            int bf = balancefactor(g);
            if (bf < -1 || bf > 1){
                rotate(x, p, g); return;
            }
            x = p;
            p = g;
            g = g->p;
        }
    }

    int balancefactor(Node *x){
        return (x->l? x->l->h : 0) - (x->r? x->r->h : 0);
    }

    void insert(string val){
        size++;
        if (!root) {
            root = new Node(val);
            return;
        } 
        Node *x = root, **p;
        while (1){
            if (val == x->val) return;
            if (val < x->val){
                if (!x->l) {
                    p = &x->l;
                    break;
                }
                x = x->l;
            } else {
                if (!x->r){
                    p = &x->r;
                    break;
                }
                x = x->r;
            }
        } 
        *p = new Node(val);
        (*p)->p = x;
        rebalance(*p);
    }

    Node *remove(string val){
        if (!root) return nullptr;
        Node *x = root;
        while (1){
            if (val == x->val) break;
            if (val < x->val){
                if (!x->l) return nullptr;
                x = x->l;
            } else {
                if (!x->r) return nullptr;
                x = x->r;
            }
        }
        size--;
        Node *ret, *rep;
        if (!x->l && !x->r){
            (x->p? x->p->l? x->p->l : x->p->r : root) = nullptr;
            delete x;
            return nullptr;
        } else if (!x->l){
            rep = x->r;
            while (rep->l) rep = rep->l;
            ret = rep->p;
            ret->l = nullptr;
            x->val = rep->val;
        } else {
            rep = x->l;
            while (rep->r) rep = rep->r;
            ret = rep->p;
            ret->r = nullptr;
            x->val = rep->val;
        }
        delete rep;
        while (ret){
            update(ret);
            int bf = balancefactor(ret);
            if (bf < -1 || bf > 1){
                Node *p, *x;
                p = bf > 0 ? ret->l : ret->r;
                x = balancefactor(p) > 0 ? p->l : p->r;
                ret = rotate(x,p,ret);
            }
            ret = ret->p;
        }
    }


    void print(){
        vector<string> ret;
        print(root, ret);
        for (auto x : ret) cout << x << ' ';
        cout << endl;
    }

    void struct_print(){
        vector<vector<string>> ret(30);
        for (int i=0; i<30; ++i) ret[i].resize(size,"NULL");
        int count = 0;
        bfs_print(root, 0, count, ret);
        for (auto x : ret){
            for (auto y : x) if (y == "NULL") cout << "      ";
            else cout << y << ' ';
            cout << endl;
        }
    }

    void push(){
        push(root);
    }

    private:

    void push(Node *x) {
        if (x->l) push(x->l);
        if (x->r) push(x->r);
        update(x);
        assert(abs(balancefactor(x))<=1);
    }

    void print(Node *x, vector<string> &ret){
        ret.push_back(x->val);
        if (x->l) print(x->l, ret);
        if (x->r) print(x->r, ret);
    }

    void bfs_print(Node *x, int dep, int &count, vector<vector<string>> &ret){
        if (x->l) bfs_print(x->l, dep+1, count, ret);
        ret[dep][count++] = x->val;
        if (x->r) bfs_print(x->r, dep+1, count, ret);
    }

} tree;

int hashs(string s){
    int ret = 0;
    for (int i=0; i<s.size(); ++i) ret += s[i];
    return ret%100;
}


int main()
{
    fastio
    string s; 
    for (int i=0; i<13; ++i){
        getline(cin, s);
        int n = s.size();
        for (int i=0;i<n-5; ++i){
            string tmp = "";
            for (int j=i; j<i+6; ++j) tmp += s[j];
            if (hashs(tmp) == 82) tree.insert(tmp);
        }
    }
    tree.struct_print();
    tree.print();
} // namespace std;
