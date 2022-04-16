#include <bits/stdc++.h>

using ll = long long;
using namespace std;

struct Node
{
    Node *left, *right;
    ll sum;
    Node() {
        left = right = nullptr;
        sum = 0;
    }
    ~Node(){
        if (left) delete left;
        if (right) delete right;
    }
};

int N; // 기본 값 설정을 위한 전역변수

struct Segtree
{
    Node *tree;
    vector<ll> arr;
    Segtree(vector<ll> &tmp){
        arr = tmp;
        N = tmp.size();
        tree = init();
    }
    ~Segtree(){
        if (tree) delete tree;
    }

    Node* init(int start=1, int end=N){
        Node *node = new Node();
        if (start == end){
            node->sum = arr[start-1];
            return node;
        }
        int mid = start + end >> 1;
        node->left = init(start, mid);
        node->right = init(mid+1, end);
        node->sum = node->left->sum + node->right->sum;
        return node;
    }

    void update(Node *node, int idx, int plus, int start=1, int end=N){
        if (start == end){
            node->sum += plus;
            return;
        }
        int mid = start + end >> 1;
        if (idx <= mid) update(node->left, idx, plus, start, mid);
        else update(node->right, idx, plus, mid+1, end);
        node->sum = node->left->sum + node->right->sum;
    }

    ll query(Node *node, int l, int r, int start=1, int end=N){
        if (end < l || r < start) return 0;
        if (l <= start && end <= r) return node->sum;
        int mid = start + end >> 1;
        return query(node->left, l, r, start, mid) + query(node->right, l, r, mid+1, end);
    }
};

