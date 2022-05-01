#include <bits/stdc++.h>

using namespace std;
const bool RED = 1;
const bool BLACK = 0;

struct Node
{
    int sz, key;
    Node *l, *r, *p;
    bool color;
    Node(){
        sz = 1;
        color = RED;
        key = 0;
        l = r = p = nullptr;
    }
    Node(int key, bool color = RED, int sz = 1) : key(key), sz(sz), color(color){
        l = r = p = nullptr;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
} ;


struct RedBlackTree{
    Node *root;
    Node* NIL;
    int size;

    RedBlackTree(){
        root = NIL = new Node(0, BLACK, 0);
        size = 0;
    }
    ~RedBlackTree(){
        if (root) delete root;
    }

    int insert(int key){
        Node *x = BST_insert(key);
        if (!x) return 0;
        size++;
        while (x) x = insert_rebalacing(x);
        NIL->p = nullptr;
        return key;
    }

    int remove(int key){
        Node *x = BST_remove(key);
        if (!x) return 0;
        size--;
        while (x) x = remove_rebalacing(x);
        NIL->p = nullptr;
        return key;
    }

    int operator[] (int k){
        Node *x = root;
        while (1){
            while (x->l && x->l->sz > k) x = x->l;
            if (x->l) k -= x->l->sz;
            if (!k--) return x->key;
            x = x->r;
        }
    }

    void print(){
        print(root);
        cout << endl;
    }

    void print_structure(){
        int h = find_height(root, 0);
        vector<vector<string>> ret(h);
        for (int i=0; i<h; ++i) ret[i].resize(size+2);
        int cnt = 0;
        print_structure(root, cnt, 0, ret);
        for (auto x : ret) {
            for (auto y : x) if (y == "") cout << "     ";
            else cout << y << ' ';
            cout << endl;
        }
    }

private:
    void update(Node *x){
        x->sz = x != NIL;
        if (x->l) x->sz += x->l->sz;
        if (x->r) x->sz += x->r->sz;
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

    Node* BST_insert(int key){
        if (root == NIL) {
            root = new Node(key, BLACK);
            root->l = root->r = NIL;
            return nullptr;
        }
        Node *x = root, **s;
        while (1){
            if (key == x->key) return nullptr;
            if (key < x->key) {
                if (x->l == NIL) {
                    s = &x->l; break;
                }
                x = x->l;
            } else {
                if (x->r == NIL) {
                    s = &x->r; break;
                }
                x = x->r;
            }
        }
        *s = new Node(key);
        (*s)->p = x;
        (*s)->l = (*s)->r = NIL;
        while (x){
            update(x); x = x->p;
        }
        return *s;
    }

    Node* BST_remove(int key){
        if (root == NIL) return nullptr;
        Node *x = root;
        while (1){
            if (key == x->key) break;
            if (key < x->key) {
                if (x->l == NIL) return nullptr;
                x = x->l;
            }
            else {
                if (x->r == NIL) return nullptr;
                x = x->r;
            } 
        }
        Node *y, *m;
        if (x->l==NIL && x->r==NIL) {
            y = x, m = NIL;
        } else if (x->l == NIL){
            y = x->r;
            while (y->l != NIL) y = y->l;
            m = y->r;
        } else {
            y = x->l;
            while (y->r != NIL) y = y->r;
            m = y->l;
        }
        x->key = y->key;
        (y->p? y->p->l == y? y->p->l : y->p->r : root) = m;
        Node *z = m->p = y->p;
        while (z) {
            update(z); z=z->p;
        }
        bool y_color = y->color, m_color = m->color;
        y->l = y->r = nullptr;
        delete y;
        if (y_color || m_color) return nullptr;
        return m;
    }

    Node* remove_rebalacing(Node *x){
        Node *p = x->p;
        if (!p) return nullptr;
        Node *s = p->l==x? p->r : p->l;
        if (s->color == RED) {
            rotate(s), swap(s->color, p->color);
            s = p->l==x? p->r : p->l;
        }
        Node *l = s->l, *r = s->r;
        if (l->color == BLACK && r->color == BLACK) {
            s->color = RED; return p;
        }
        if (l->color == RED && r->color == BLACK){
            rotate(l); swap(l->color, s->color);
            l = s; s = r;
        }
        rotate(s);
        swap(s->color, p->color);
        r->color = BLACK;
        NIL->p = nullptr;
    }


    Node* insert_rebalacing(Node *x){
        Node *p = x->p;
        if (!p || p->color == BLACK) return nullptr;
        Node *g = p->p, *s = g->l==p? g->r : g->l;
        if (s->color == RED) {
            p->color = s->color = BLACK;
            g->color = g==root? BLACK : RED;
            return g;
        }
        if ((p->l==x) != (g->l==p)) rotate(x), swap(x, p);
        rotate(p);
        swap(p->color, g->color);
        return nullptr;
    }

    void print(Node *x){
        if (x == NIL) return;
        print(x->l);
        cout << x->key << "  ";
        print(x->r);
    }

    int find_height(Node *x, int dep){
        if (x == NIL) return dep;
        return max(find_height(x->l, dep+1), find_height(x->r, dep+1));
    }

    void print_structure(Node *x, int &cnt, int dep, vector<vector<string>> &ret){
        if (x==NIL) return;
        print_structure(x->l, cnt, dep+1, ret);
        ret[dep][cnt++] = to_string(x->key) +"-"+ (x->color == RED? "R" : "B");
        print_structure(x->r, cnt, dep+1, ret);
    }
};


int main()
{
    RedBlackTree Rb;
    set<int> s;
    for (int i=1; i<=20; ++i) {
        int x = rand()%100;
        cout << x << ' ';
        Rb.insert(x);
    }

    Rb.remove(36);
    Rb.remove(62);
    cout << endl; 
    Rb.print_structure();
} // namespace std;