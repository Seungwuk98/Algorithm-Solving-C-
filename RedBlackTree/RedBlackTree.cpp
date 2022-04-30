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
    Node(int key, bool color = RED, int sz = 1) : key(key), sz(sz){
        color = RED;
        l = r = p = nullptr;
    }
    ~Node(){
        if (l) delete l;
        if (r) delete r;
    }
} ;


struct RedBlackTree{
    Node *root;
    Node* NIL = new Node(NULL, BLACK, 0);

    RedBlackTree(){
        root = NIL;
    }
    ~RedBlackTree(){
        if (root) delete root;
    }

    int insert(int key){
        Node* x = BST_insert(key);
        
        return key;
    }

    Node* BST_remove(int key){
        if (root == NIL) return nullptr;
        Node *x = root;
        while (1) {
            if (key == x->key) break;
            if (key < x->key) if ((x = x->l) == NIL) return nullptr;
            else if ((x = x->r) == NIL) return nullptr;
        }
        Node *m, *c, *y;
        if (x->l==NIL && x->r==NIL){
            x->l = x->r = nullptr;
            y = x->p;
            c = NIL;
            delete x;
        } else if (x->l!=NIL){
            m = x->l; y = x;
            while (m->r!=NIL) {
                y=m; m=m->r;
            } 
            
        } else {

        }
    }


    

private:
    void update(Node *x){
        x->sz = 1;
        if (x->l) x->sz += x->l->sz;
        if (x->r) x->sz += x->r->sz;
    }


    void rotate(Node *x){
        Node *p = x->p, *a;
        if (p->l == x){
            p->l = a = x->r;
            x->r = p;
        } else {
            p->r = a = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (a) a->p = p;
        (x->p? x->p->l == x ? x->p->l : x->p->r : root) = x;
        update(p);
        update(x);
    }

    Node* BST_insert(int key){
        if (root==NIL){
            root = new Node(key, BLACK);
            root->l = root->r = NIL;
            return root;
        }
        Node *x, **s;
        while (1){
            if (key == x->key) return nullptr;
            if (key < x->key){
                if (x->l == NIL) { s=&x->l; break; }
                x = x->l;
            } else {
                if (x->r == NIL) { s=&x->r; break; }
                x = x->r;
            }
        }
        *s = new Node(key);
        (*s)->p = x;
        (*s)->l = (*s)->r = NIL;
        while (x){
            update(x);
            x=x->p;
        }
        return *s;
    }

    Node* upRebalance(Node *x){
        Node *p = x->p;
        if (!p || p->color == BLACK || !p->p) return nullptr;
        Node *g = p->p;
        Node *s = g->l==p? g->r : g->l;
        if (s->color == RED) {
            s->color = BLACK;
            p->color = BLACK;
            return g;
        }
        if ((p->l==x) != (g->l==p)) rotate(x), swap(x,p);
        rotate(p);
        p->color = BLACK;
        g->color = RED;
        return nullptr;
    }

    
};


int main()
{
    
} // namespace std;
