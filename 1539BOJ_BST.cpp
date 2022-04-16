#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;

    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

struct BST
{
    Node *root;
    int height = 1;

    void insert(int key)
    {
        if (!root)
            root = new Node(key);
        else
        {
            Node *node = root;
            int h = 1;
            while (1)
            {
                if (key == node->key)
                    return;
                else if (key < node->key)
                {
                    if (!node->left)
                    {
                        node->left = new Node(key);
                        height += h + 1;
                        return;
                    }
                    node = node->left;
                }
                else
                {
                    if (!node->right)
                    {
                        node->right = new Node(key);
                        height += h + 1;
                        return;
                    }
                    node = node->right;
                }
                h++;
            }
        }
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    BST bst = BST();

    while (n--)
    {
        int x;
        scanf("%d", &x);
        bst.insert(x);
    }
    printf("%d", bst.height);

} // namespace std;
