#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#define all(v) v.begin(), v.end()

using ll = long long;
using namespace std;

struct Node
{
    Node *l, *r, *p;
    ll val, sum, min, max;
    int cnt;
    Node()
    {
        l = r = p = nullptr;
        val = sum = min = max = 0;
        cnt = 1;
    }
    ~Node()
    {
        if (l)
            delete l;
        if (r)
            delete r;
    }
};

struct SplayTree
{
    Node *tree;
    Node *dummyL;
    Node *dummyR;
    int length = 0;

    SplayTree()
    {
        tree = nullptr;
    }
    ~SplayTree()
    {
        if (tree)
            delete tree;
    }

    void rotate(Node *x)
    {
        Node *p = x->p;
        Node *a;
        if (p->l == x)
        {
            p->l = a = x->r;
            x->r = p;
        }
        else
        {
            p->r = a = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (a)
            a->p = p;
        (x->p ? x->p->l == p ? x->p->l : x->p->r : tree) = x;
        update(p);
        update(x);
    }

    void splay(Node *x)
    {
        while (x->p)
        {
            Node *p = x->p;
            Node *g = p->p;
            if (g)
                rotate((g->l == p) == (p->l == x) ? p : x);
            rotate(x);
        }
    }

    void update(Node *x)
    {
        x->sum = x->val;
        x->cnt = 1;
        if (x->l)
        {
            x->sum += x->l->sum;
            x->cnt += x->l->cnt;
        }
        if (x->r)
        {
            x->sum += x->r->sum;
            x->cnt += x->r->cnt;
        }
    }

    void kth(int k)
    {
        Node *x = tree;
        while (1)
        {
            while (x->l && x->l->cnt > k)
            {
                x = x->l;
            }
            if (x->l)
                k -= x->l->cnt;
            if (!k--)
                break;
            x = x->r;
        }
        splay(x);
    }

    void add(int i, ll z)
    {
        kth(i);
        tree->sum += z;
        tree->val += z;
    }

    void init(int n)
    {
        if (tree)
            delete (tree);
        length = n;
        tree = dummyL = new Node();
        Node *pre = dummyL;
        pre->cnt = n + 2;
        while (n--)
        {
            Node *node = new Node();
            node->cnt = n + 2;
            pre->r = node;
            node->p = pre;
            pre = node;
        }
        dummyR = new Node();
        dummyR->cnt = 1;
        pre->r = dummyR;
        dummyR->p = pre;
    }

    void interval(int l, int r)
    {
        kth(l - 1);
        Node *x = tree;
        tree = x->r;
        tree->p = nullptr;
        kth(r - l + 1);
        x->r = tree;
        tree->p = x;
        tree = x;
    }

    void print()
    {
        for (int i = 1; i <= length; ++i)
        {
            kth(i);
            cout << tree->val << ' ';
        }
        cout << '\n';
    }

} tree;