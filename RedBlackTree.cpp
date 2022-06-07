#include <bits/stdc++.h>

using namespace std;

/********* 색 정의 *********/
const bool RED = 1;
const bool BLACK = 0;
/********* 색 정의 *********/

struct Node
{
    int subtree_size, key;
    Node *left, *right, *parent;
    bool color;
    Node()
    {
        subtree_size = 1;
        color = RED;
        key = 0;
        left = right = parent = nullptr;
    }
    Node(int key, bool color = RED, int subtree_size = RED)
        : key(key), subtree_size(subtree_size), color(color)
    {
        left = right = parent = nullptr;
    }
    ~Node()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
};

struct RedBlackTree
{
    Node *root;
    Node *NIL;
    int size;

    RedBlackTree()
    {
        root = NIL = new Node(0, BLACK, 0);
        size = 0;
    }
    ~RedBlackTree()
    {
        if (root)
            delete root;
    }

    /**************************************************************************************
     * OS-Insert(T, x)에 해당하는 함수
     * 로직
     * 1. BST_insert 함수를 호출,
     *    BST_insert 함수는 key에 해당하는 노드가 있으면 nullptr를 리턴,
     *    없으면 노드를 생성하여 적절한 자리에 삽입하고,
     *    적절한 사이즈를 가질 수 있도록 루트까지 각 노드의 서브트리 size를 갱신한 뒤,
     *    새로 삽입된 노드를 리턴합니다.
     * 2. 새로 삽입된 노드가 없다면 0을 리턴하여 종료하고,
     * 3. 아니면 전체 트리 사이즈를 늘린 뒤,
     * 4. 해당 노드가 존재하지 않을 때까지 insert_rabalancing을 호출합니다.
     *    insert_rebalancing은 해당 노드 case를 분석하여 해결하고,
     *    해결되지 않은 노드를 다시 반환합니다.
     *    루트 노드를 넘거나, 해결이 모두 되었다면 반복문이 종료됩니다.
     * 5. key를 리턴합니다.
     ****************************************************************************************/
    int insert(int key)
    {
        Node *currNode = BST_insert(key);
        if (!currNode)
            return 0;
        size++;
        while (currNode)
            currNode = insert_rebalacing(currNode);
        return key;
    }

    /***************************************************************************************
     * OS-Delete(T, x)에 해당하는 함수
     * 로직
     * 1. BST_remove 함수를 호출,
     *    BST_remove 함수는 key에 해당하는 노드가 있으면 제거하고, 적절한 노드의 값을 복사한 뒤,
     *    제거합니다. 단 이때, 제거된 노드의 부모부터 루트까지 모든 서브트리 size를 갱신하고,
     *    제거된 자리를 대체한 노드를 반환합니다.
     *    Red Black Tree property에 어긋나지 않는 경우, 성공했음을 구별하기 위해 의미없는 root를 리턴합니다.
     *    key에 해당하는 노드가 없다면 nullptr을 반환합니다.
     * 2. 해당 노드가 존재하지 않았다면 0을 리턴하고,
     * 3. 아니라면 사이즈를 줄인 뒤,
     * 4. 노드가 루트에 도달하거나, rebalancing이 완료될 때까지 remove_rebalancing 함수를 호출합니다.
     *    remove_rebalancing 함수는 해당 노드 case를 분석하여 해결한 뒤,
     *    해결되지 않은 노드를 리턴합니다.
     * 5. remove_rebalancing 함수에서 NIL의 부모포인터를 이용해야하는 경우가 생기므로,
     *    마지막에 NIL의 부모 포인터를 초기화합니다.
     * 6. key를 리턴합니다.
     ****************************************************************************************/
    int remove(int key)
    {
        Node *currNode = BST_remove(key);
        if (!currNode)
            return 0;
        size--;
        while (currNode)
            currNode = remove_rebalacing(currNode);
        NIL->parent = nullptr;
        return key;
    }

    /**************************************************************************************
     * 직관적으로 Red Black Tree의 원소를 접근하기 위해, [] operator를 오버라이딩 했습니다.
     * Red Black Tree의 원소를 0-base index로 접근할 수 있습니다.
     * 로직
     * 1. 해당 노드의 왼쪽 자식 노드의 서브트리 size가 k보다 크다면, 찾는 원소는 왼쪽 서브트리에 있으므로 내려갑니다.
     * 2. k보다 작거나 같다면, 나 자신 또는 오른쪽 서브트리에 존재하므로
     * 3. 왼쪽 자식 노드의 서브트리의 크기가 k와 같으면 나 자신의 값을 리턴
     * 4. 아니면 오른쪽 자식 노드에서 k-(left.subtree_size)-1 번째 노드를 찾으면 됩니다.
     * 5. 3이 될 때까지 반복문을 돌립니다.
     ***************************************************************************************/
    int operator[](int k)
    {
        if (k >= size || k < 0)
            return 0;
        Node *currNode = root;
        while (1)
        {
            while (currNode->left && currNode->left->subtree_size > k)
                currNode = currNode->left;
            if (currNode->left)
                k -= currNode->left->subtree_size;
            if (!k--)
                return currNode->key;
            currNode = currNode->right;
        }
    }

    /**************************************************************************************
     * OS-Select(T, i)에 해당하는 함수
     * 오버라이딩한 operator[]함수를 이용하여 k번째 작은 원소를 리턴합니다.
     ***************************************************************************************/
    int kth_element(int k)
    {
        return operator[](k - 1);
    }

    /**************************************************************************************
     * OS-Rank(T, x)에 해당하는 함수
     * 로직
     * 1. BST_search함수를 이용하여 해당하는 노드를 찾아 반환받습니다.
     * 2. 그러한 노드가 없다면 0을 리턴하고
     * 3. 아니면 해당 노드의 왼쪽 자식 노드 + 1에서부터 rank를 계산하기 시작합니다.
     * 4. 부모로 올라가며 반약 부모의 오른쪽 자식인 경우가 생기면 부모의 왼쪽 서브트리 + 1만큼
     *    더 작은 원소가 있다는 뜻이므로 더해줍니다.
     * 5. 루트까지 진행하고, 값을 리턴합니다.
     ***************************************************************************************/
    int rank(int key)
    {
        Node *currNode = BST_search(key);
        if (!currNode)
            return 0;
        int ret = currNode->left->subtree_size + 1;
        while (currNode->parent)
        {
            if (currNode->parent->right == currNode)
                ret += currNode->parent->left->subtree_size + 1;
            currNode = currNode->parent;
        }
        return ret;
    }

private:
    /**************************************************************************************
     * 해당 노드의 서브트리 사이즈를 갱신합니다. 이때 NIL은 반드시 0이 되도록 했습니다.
     **************************************************************************************/
    void update(Node *currNode)
    {
        currNode->subtree_size = currNode != NIL;
        if (currNode->left)
            currNode->subtree_size += currNode->left->subtree_size;
        if (currNode->right)
            currNode->subtree_size += currNode->right->subtree_size;
    }

    /**************************************************************************************
     * 해당 노드가 오른쪽, 왼쪽으로 내려가는 회전이 아닌
     * 노드가 부모를 제치고 올라가는 방식으로 회전을 구현했습니다.
     * 모든 rebalancing 과정은 해당 코드로 진행했습니다.
     * (x)가 currNode입니다.
     * case 1                          case 2
     *      p                (x)               p                   (x)
     *     / \               / \              / \                  / \
     *   (x)  r      ->     l   p            l  (x)      ->       p   r
     *   / \                   / \              / \              / \
     *  l   t                 t   r            t   r            l   t
     ***************************************************************************************/
    void rotate(Node *currNode)
    {
        Node *parent = currNode->parent;
        Node *tmpNode;
        if (parent->left == currNode)
        {
            // case 1 : 부모의 왼쪽 자식일 때,
            parent->left = tmpNode = currNode->right;
            currNode->right = parent;
        }
        else
        {
            // case 2 : 부모의 오른쪽 자식일 때,
            parent->right = tmpNode = currNode->left;
            currNode->left = parent;
        }
        // 두 케이스 모두 공통적으로 진행해야하는 것
        currNode->parent = parent->parent;
        parent->parent = currNode;
        if (tmpNode)
            tmpNode->parent = parent;
        (currNode->parent ? currNode->parent->left == parent ? currNode->parent->left : currNode->parent->right : root) = currNode;
        // 부모 자식 관계가 바뀐 두 노드에 대해 다시 서브트리 사이즈를 갱신
        update(parent);
        update(currNode);
    }

    /********************************************************************
     * BST의 insert를 그대로 비재귀 방식으로 구현한 것.
     * 1. root 가 NIL이면 루트를 갱신
     * 2. 해당 키가 존재한다면 nullptr를 리턴. 함수 종료
     * 3. 검색하며 계속 내려가다가, NIL을 만나게 되면 해당 자리를 포인터로 받음(이중포인터)
     * 4. 해당 자리에 새로운 노드를 삽입하고, 루트가 될 때까지 서브트리 사이즈 갱신
     * 5. 새로운 노드를 리턴
     *********************************************************************/
    Node *BST_insert(int key)
    {
        if (root == NIL)
        {
            // root가 NIL이면 새로운 루트 생성
            root = new Node(key, BLACK);
            root->left = root->right = NIL;
            return root;
        }
        // 넣을 자리를 찾아 내려감. **retNode는 새로운 노드를 넣을 자리를 가리킬 이중 포인터
        Node *currNode = root, **retNode;
        while (1)
        {
            if (key == currNode->key)
                return nullptr;
            if (key < currNode->key)
            {
                if (currNode->left == NIL)
                {
                    retNode = &currNode->left;
                    break;
                }
                currNode = currNode->left;
            }
            else
            {
                if (currNode->right == NIL)
                {
                    retNode = &currNode->right;
                    break;
                }
                currNode = currNode->right;
            }
        }
        // 자리에 새로운 노드를 넣고 갱신
        *retNode = new Node(key);
        (*retNode)->parent = currNode;
        (*retNode)->left = (*retNode)->right = NIL;
        // 서브트리 사이즈를 업데이트
        while (currNode)
        {
            update(currNode);
            currNode = currNode->parent;
        }
        return *retNode;
    }

    /*******************************************************************
     * BST의 delete 작업을 비재귀 방식으로 구현한 것
     * 1. root가 NIL이면 그대로 작업 종료. nullptr 리턴
     * 2. 키 값을 비교하며 내려가다가 해당 키의 노드가 있으면 break
     * 3. 아니면 nullptr를 리턴
     * 4. (1) 두 자식노드가 존재하지 않을 때, (2) 오른쪽 노드가 존재할 때 (3) 왼쪽 노드가 존재할 때
     *    각 경우에 대해 (실제로)삭제할 노드와, 그 자리를 대체할 노드를 저장.
     *    (1) 의 경우 삭제할 노드는 자신이며 대체할 노드는 NIL
     *    (2) 의 경우 삭제할 노드는 오른쪽 서브트리 가장 작은 값이며, 대체할 노드는 삭제할 노드의 오른쪽 자식
     *    (3) 의 경우 삭제할 노드는 왼쪽 서브트리 가장 큰 값이며, 대체할 노드는 삭제할 노드의 왼쪽 자식
     * 5. 원래 삭제되는 노드의 키값을 변경하고
     * 6. 노드를 삭제한 뒤, 그 부모부터 루트까지 다시 서브트리 size를 갱신
     * 7. 삭제한 노드와 대체할 노드의 색이 서로 달랐다면, rebalancing을 진행할 필요가 없음
     *    하지만 삭제를 완료했다는 것을 확인해야하므로 의미없는 노드인 root를 리턴
     * 8. 아닌 경우 대체할 노드를 리턴
     ********************************************************************/
    Node *BST_remove(int key)
    {
        // root 가 NIL이면 nullptr 리턴
        if (root == NIL)
            return nullptr;
        // 삭제되는 노드 찾기
        Node *currNode = root;
        while (1)
        {
            if (key == currNode->key)
                break;
            if (key < currNode->key)
            {
                if (currNode->left == NIL)
                    return nullptr;
                currNode = currNode->left;
            }
            else
            {
                if (currNode->right == NIL)
                    return nullptr;
                currNode = currNode->right;
            }
        }

        // 자식노드에 따라 실제로 삭제될 노드와 그것을 대체할 노드를 선택
        Node *delNode, *retNode;
        if (currNode->left == NIL && currNode->right == NIL)
        {
            delNode = currNode, retNode = NIL;
        }
        else if (currNode->left == NIL)
        {
            delNode = currNode->right;
            while (delNode->left != NIL)
                delNode = delNode->left;
            retNode = delNode->right;
        }
        else
        {
            delNode = currNode->left;
            while (delNode->right != NIL)
                delNode = delNode->right;
            retNode = delNode->left;
        }
        currNode->key = delNode->key;
        (delNode->parent ? delNode->parent->left == delNode ? delNode->parent->left : delNode->parent->right : root) = retNode;
        Node *updateNode = retNode->parent = delNode->parent;
        // 삭제되는 노드의 부모노드부터 서브트리 사이즈를 갱신
        while (updateNode)
        {
            update(updateNode);
            updateNode = updateNode->parent;
        }
        // 삭제되기 전에 미리 색을 저장하고, NIL 삭제 방지를 위해 자식들을 모두 nullptr로 지정
        bool del_color = delNode->color, ret_color = retNode->color;
        retNode->color = BLACK;
        delNode->left = delNode->right = nullptr;
        delete delNode;
        /* 두 색이 다르다면 논리 전개상 nullptr을 반환하는게 맞으나,
        nullptr을 반환할 경우 remove 성공 유무를 판단 불가
        따라서 의미없는 root 를 반환 */
        if (del_color != ret_color)
            return root;
        return retNode;
    }

    /*******************************************************************
     * key값에 해당하는 노드를 찾아서 리턴
     * 없으면 nullptr을 리턴
     ********************************************************************/
    Node *BST_search(int key)
    {
        if (root == NIL)
            return nullptr;
        Node *currNode = root;
        while (1)
        {
            if (key == currNode->key)
                return currNode;
            if (key < currNode->key)
            {
                if (currNode->left == NIL)
                    return nullptr;
                currNode = currNode->left;
            }
            else
            {
                if (currNode->right == NIL)
                    return nullptr;
                currNode = currNode->right;
            }
        }
    }

    /******************************************************************
     * insert했을 때 실제로 rebalncing을 수행하는 함수
     *******************************************************************/
    Node *insert_rebalacing(Node *currNode)
    {
        Node *parent = currNode->parent;
        // 부모가 존재하지 않거나, 그 색이 BLACK이면 더 이상 진행할 필요 없습니다.
        if (!parent || parent->color == BLACK)
            return nullptr;
        // 부모가 RED인 경우만 진행하며, 루트는 BLACK이므로 만드시 부모의 부모가 존재합니다.
        Node *grandp = parent->parent, *sibling = grandp->left == parent ? grandp->right : grandp->left;
        if (sibling->color == RED)
        {
            // case 1 : sibling이 RED인 경우 parent와 sibling을 BLACK으로 바꾸고
            //          부모의 부모의 색을 루트면 BLACK 아니면 RED로 바꿉니다.
            //          이 경우 부모의 부모는 같은 문제를 가지므로 그것을 리턴합니다.
            parent->color = sibling->color = BLACK;
            grandp->color = grandp == root ? BLACK : RED;
            return grandp;
        }
        // case 2 : 조부모-부모-자식 노드가 일직선이 아닌 경우
        //          자식노드를 한번 rotate함수로 올려주어 일직선으로 만들어줍니다.
        //          이 때 자식노드와 부모노드의 역할을 바꾸어줍니다.
        if ((parent->left == currNode) != (grandp->left == parent))
            rotate(currNode), swap(currNode, parent);
        // case 3 : 조부모-부모-자식 노드가 일직선인 경우
        //          부모 노드를 rotate함수로 올려주고, 조부모 노드와 색을 교환하면 끝입니다.
        rotate(parent);
        swap(parent->color, grandp->color);
        return nullptr;
    }

    /********************************************************************
     * remove했을 때 실제로 rebalancing을 수행하는 함수
     *********************************************************************/
    Node *remove_rebalacing(Node *currNode)
    {
        Node *parent = currNode->parent;
        // 부모 노드가 존재하지 않으면 nullptr을 리턴
        if (!parent)
            return nullptr;
        // 자식이 부모의 왼쪽자식인지, 오른쪽 자식인지에 따라 논리가 상이
        bool isLeft = parent->left == currNode;
        Node *sibling = isLeft ? parent->right : parent->left;
        if (sibling->color == RED)
        {
            // case 1 : sibling이 RED인 경우, sibling을 rotate 함수로 올려주고
            //          부모와 색을 바꿔줍니다.
            //          이때 sibling의 역할을 할 노드가 적절하게 바뀌어야 합니다.
            rotate(sibling), swap(sibling->color, parent->color);
            sibling = isLeft ? parent->right : parent->left;
        }
        Node *l = sibling->left, *r = sibling->right;
        // sibling의 자식 역시, isLeft에 따라 바뀌어야합니다.
        if (!isLeft)
            swap(l, r);
        if (l->color == BLACK && r->color == BLACK)
        {
            // case 2 : 만약 sibling의 두 자식이 모두 BLACK이라면
            //          부모의 색은 BLACK으로, sibling의 색은 RED로 바뀌어야 하고,
            //          부모의 색이 RED였던 경우 더 이상 진행할 필요가 없으므로 nullptr를 리턴합니다.
            bool p_color = parent->color;
            parent->color = BLACK;
            sibling->color = RED;
            return p_color == RED ? nullptr : parent;
        }
        if (l->color == RED && r->color == BLACK)
        {
            // case 3 : 만일 l의 색이 RED이고 r의 색이 BLACK이라면
            //          l을 rotate로 올려주어 일직선을 만들어주고
            //          r과 sibling의 역할을 적절하게 바꾸어줍니다.
            rotate(l);
            swap(l->color, sibling->color);
            r = sibling, sibling = l;
        }
        // case 4 : l의 색이 BLACK r의 색이 RED일 때
        //          sibling을 rotate하여 올려주고, sibling의 색과 부모의 색을 교환합니다.
        rotate(sibling);
        swap(sibling->color, parent->color);
        r->color = BLACK;
        NIL->parent = nullptr;
        return nullptr;
    }
};

/**********************************체커 프로그램*************************************/
/************************************************************************************/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

void checker_program(vector<pair<char, int>> &Q, vector<int> &result)
{
    ofstream cout_checker;
    cout_checker.open("checker.txt");
    ordered_set o_set;

    char op;
    int x, y;
    for (int i = 0; i < Q.size(); ++i)
    {
        tie(op, x) = Q[i];
        if (op == 'I')
        {
            if (o_set.find(x) == o_set.end())
                o_set.insert(x), y = x;
            else
                y = 0;
        }
        else if (op == 'D')
        {
            if (o_set.find(x) != o_set.end())
                o_set.erase(x), y = x;
            else
                y = 0;
        }
        else if (op == 'S')
        {
            if (1 <= x && x <= o_set.size())
                y = *o_set.find_by_order(x - 1);
            else
                y = 0;
        }
        else
        {
            if (o_set.find(x) != o_set.end())
                y = o_set.order_of_key(x) + 1;
            else
                y = 0;
        }
        cout_checker << (result[i] == y) << '\n';
    }
}
/************************************************************************************/
/**********************************체커 프로그램*************************************/

/**********************************체커 프로그램2*************************************/
/************************************************************************************/
// #define all(v) v.begin(), v.end()
// void checker_program2(vector<pair<char, int>> &Q, vector<int> &result){
//     ofstream cout_checker;
//     cout_checker.open("checker.txt");
//     vector<int> check;
//     char op; int x, y;
//     for (int i=0; i<Q.size(); ++i) {
//         tie(op, x) = Q[i];
//         if (op == 'I') {
//             if (find(all(check), x) == check.end()) {
//                 int j = lower_bound(all(check), x) - check.begin();
//                 check.insert(check.begin()+j, x);
//                 y = x;
//             } else y = 0;
//         } else if (op == 'D') {
//             auto iter = find(all(check), x);
//             if (iter != check.end()) {
//                 check.erase(iter);
//                 y = x;
//             } else y = 0;
//         } else if (op == 'S') {
//             if (1<=x && x<=check.size()) y = check[x-1];
//             else y = 0;
//         } else {
//             int j = lower_bound(all(check), x) - check.begin();
//             if (j >= check.size() || check[j] != x) y = 0;
//             else y = j+1;
//         }
//         cout_checker << (result[i] == y) << '\n';
//     }

// }
/************************************************************************************/
/**********************************체커 프로그램2*************************************/

int main()
{
    /**************** 입출력 설정 ***************/
    ifstream cin_input;
    cin_input.open("input_9.txt");
    ofstream cout_output;
    cout_output.open("output9.txt");
    cin_input.tie(0);
    ios_base::sync_with_stdio(0);
    /**************** 입출력 설정 ***************/

    /**************** 선언 및 입력, 출력 ****************/
    RedBlackTree Rb;
    vector<pair<char, int>> Q;
    char op;
    int x;
    while (cin_input >> op >> x)
    {
        Q.push_back({op, x});
        cout_output << op << ' ' << x << '\n';
    }
    /**************** 선언 및 입력, 출력 ****************/

    /**************** Solve ****************/
    vector<int> result;
    int y;
    for (auto q : Q)
    {
        tie(op, x) = q;
        if (op == 'I')
            y = Rb.insert(x);
        else if (op == 'D')
            y = Rb.remove(x);
        else if (op == 'S')
            y = Rb.kth_element(x);
        else
            y = Rb.rank(x);
        cout_output << y << '\n';
        result.push_back(y);
    }
    /**************** Solve ****************/

    /**************** Checker program *****************/
    // checker_program2(Q, result);
    /**************** Checker program *****************/

} // namespace std;
