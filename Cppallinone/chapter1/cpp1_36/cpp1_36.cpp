#include <iostream>

using namespace std;
void count(int n)
{
    if (n < 0)
        return;
    cout << n << endl;
    count(n - 1);
}

int fac(int n)
{
    return n ? n * fac(n - 1) : 1;
}

int fib(int n)
{
    return (!n || n == 1) ? 1 : fib(n - 1) + fib(n - 2);
}

struct Node
{
    int value;
    Node *left;
    Node *right;
};

void order(Node *n)
{
    if (!n)
        return;
    order(n->left);
    order(n->right);
    cout << (n->value) << " ";
}

int main()
{
    Node node0{0};
    Node node1{1};
    Node node2{2};
    Node node3{3};
    Node node4{4};
    Node node5{5};
    Node node6{6};
    Node node7{7};
    Node node8{8};
    Node node9{9};
    node0.left = &node1;
    node1.left = &node2;
    node1.right = &node3;
    node3.right = &node4;
    node0.right = &node5;
    node5.left = &node6;
    node6.right = &node7;
    node5.right = &node8;
    node8.left = &node9;
    order(&node0);
} // namespace std;
