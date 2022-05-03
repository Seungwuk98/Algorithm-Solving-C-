#include <bits/stdc++.h>

using namespace std;
const bool RED = 1;
const bool BLACK = 0;

struct Node
{
    
    int subtree_size, key;
    Node *left, *right, *parent;
    bool color;
    Node(){
        subtree_size = 1;
        color = RED;
        key = 0;
        left = right = parent = nullptr;
    }
    Node(int key, bool color = RED, int subtree_size = RED) 
        : key(key), subtree_size(subtree_size), color(color)   {
        left = right = parent = nullptr;
    }
    ~Node(){
        if (left) delete left;
        if (right) delete right;
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
        Node *currNode = BST_insert(key);
        if (!currNode) return 0;
        size++;
        while (currNode) currNode = insert_rebalacing(currNode);
        NIL->parent = nullptr;
        return key;
    }

    int remove(int key){
        Node *currNode = BST_remove(key);
        if (!currNode) return 0;
        size--; 
        while (currNode) {
            currNode = remove_rebalacing(currNode);
        } 
        NIL->parent = nullptr;
        return key;
    }

    int operator[] (int k){
        Node *currNode = root;
        while (1){
            while (currNode->left && currNode->left->subtree_size > k) currNode = currNode->left;
            if (currNode->left) k -= currNode->left->subtree_size;
            if (!k--) return currNode->key;
            currNode = currNode->right;
        }
    }

    int kth_element(int k){
        if (k > size) return 0;
        return operator[] (k-1);
    }

    int rank(int key) {
        Node *currNode = BST_search(key);
        if (!currNode) return 0;
        int ret = currNode->left->subtree_size+1;
        while (currNode->parent){
            if (currNode->parent->right == currNode) ret += currNode->parent->left->subtree_size+1;
            currNode = currNode->parent;
        }
        return ret;
    }
private:
    void update(Node *currNode){
        currNode->subtree_size = currNode != NIL;
        if (currNode->left) currNode->subtree_size += currNode->left->subtree_size;
        if (currNode->right) currNode->subtree_size += currNode->right->subtree_size;
    }

    void rotate(Node *currNode){
        Node *parent = currNode->parent;
        Node *tmpNode;
        if (parent->left == currNode){
            parent->left = tmpNode = currNode->right;
            currNode->right = parent;
        } else{
            parent->right = tmpNode = currNode->left;
            currNode->left = parent;
        }
        currNode->parent = parent->parent;
        parent->parent = currNode;
        if (tmpNode) tmpNode->parent = parent;
        (currNode->parent ? currNode->parent->left == parent ? currNode->parent->left : currNode->parent->right : root) = currNode;
        update(parent);
        update(currNode);
    }

    Node* BST_insert(int key){
        if (root == NIL) {
            root = new Node(key, BLACK);
            root->left = root->right = NIL;
            return root;
        }
        Node *currNode = root, **retNode;
        while (1){
            if (key == currNode->key) return nullptr;
            if (key < currNode->key) {
                if (currNode->left == NIL) {
                    retNode = &currNode->left; break;
                }
                currNode = currNode->left;
            } else {
                if (currNode->right == NIL) {
                    retNode = &currNode->right; break;
                }
                currNode = currNode->right;
            }
        }
        *retNode = new Node(key);
        (*retNode)->parent = currNode;
        (*retNode)->left = (*retNode)->right = NIL;
        while (currNode){
            update(currNode); currNode = currNode->parent;
        }
        return *retNode;
    }

    Node* BST_remove(int key){
        if (root == NIL) return nullptr;
        Node *currNode = root;
        while (1){
            if (key == currNode->key) break;
            if (key < currNode->key) {
                if (currNode->left == NIL) return nullptr;
                currNode = currNode->left;
            }
            else {
                if (currNode->right == NIL) return nullptr;
                currNode = currNode->right;
            } 
        }
        Node *delNode, *retNode;
        if (currNode->left==NIL && currNode->right==NIL) {
            delNode = currNode, retNode = NIL;
        } else if (currNode->left == NIL){
            delNode = currNode->right;
            while (delNode->left != NIL) delNode = delNode->left;
            retNode = delNode->right;
        } else {
            delNode = currNode->left;
            while (delNode->right != NIL) delNode = delNode->right;
            retNode = delNode->left;
        }
        currNode->key = delNode->key;
        (delNode->parent? delNode->parent->left == delNode? delNode->parent->left : delNode->parent->right : root) = retNode;
        Node *z = retNode->parent = delNode->parent;
        while (z) {
            update(z); z=z->parent;
        }
        bool y_color = delNode->color, m_color = retNode->color;
        retNode->color = BLACK;
        delNode->left = delNode->right = nullptr;
        delete delNode;
        /* 논리 전개상 nullptr을 반환하는게 맞으나, 
        nullptr을 반환할 경우 remove 성공 유무를 판단 불가 
        따라서 의미없는 root 를 반환 */
        if (y_color != m_color) return root;
        return retNode;
    }

    Node* BST_search(int key){
        if (root == NIL) return nullptr;
        Node *currNode = root;
        while (1){
            if (key == currNode->key) return currNode;
            if (key < currNode->key) {
                if (currNode->left == NIL) return nullptr;
                currNode = currNode->left;
            } else {
                if (currNode->right == NIL) return nullptr;
                currNode = currNode->right;
            }
        }
    }

    Node* remove_rebalacing(Node *currNode){
        Node *parent = currNode->parent;
        if (!parent) return nullptr;
        bool isLeft = parent->left==currNode;
        Node *sibling = isLeft? parent->right : parent->left;
        if (sibling->color == RED) {
            rotate(sibling), swap(sibling->color, parent->color);
            sibling = isLeft? parent->right : parent->left;
        }
        Node *l = sibling->left, *r = sibling->right;
        if (!isLeft) swap(l, r);
        if (l->color == BLACK && r->color == BLACK) {
            bool p_color = parent->color;
            parent->color = BLACK;
            sibling->color = RED; 
            return p_color == RED? nullptr : parent;
        }
        if (l->color == RED && r->color == BLACK){
            rotate(l); swap(l->color, sibling->color);
            r = sibling, sibling = l;
        }
        rotate(sibling);
        swap(sibling->color, parent->color);
        r->color = BLACK;
        NIL->parent = nullptr;
    }


    Node* insert_rebalacing(Node *currNode){
        Node *parent = currNode->parent;
        if (!parent || parent->color == BLACK) return nullptr;
        Node *grandp = parent->parent, *sibling = grandp->left==parent? grandp->right : grandp->left;
        if (sibling->color == RED) {
            parent->color = sibling->color = BLACK;
            grandp->color = grandp==root? BLACK : RED;
            return grandp;
        }
        if ((parent->left==currNode) != (grandp->left==parent)) rotate(currNode), swap(currNode, parent);
        rotate(parent);
        swap(parent->color, grandp->color);
        return nullptr;
    }
};


int main()
{
    RedBlackTree Rb;
    vector<pair<char,int>> Q;
    char op; int x;
    while (cin >> op >> x){
        Q.push_back({op, x});
        cout << op << ' ' << x << endl;
    }
    for (auto q : Q){
        tie(op, x) = q; 
        if (op == 'I') cout << Rb.insert(x) << endl;
        else if (op == 'D') cout << Rb.remove(x) << endl;
        else if (op == 'S') cout << Rb.kth_element(x) << endl;
        else cout << Rb.rank(x) << endl;
    }
} // namespace std;

