#include <stdio.h>
#include <stdlib.h>
typedef struct nodeType LinkedNode;
struct nodeType
{
    int val;
    LinkedNode *next;
};
LinkedNode *createNode(int x)
{
    LinkedNode *newNode;
    newNode = (LinkedNode *)malloc(sizeof(LinkedNode));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}
typedef struct listType SLList;
struct listType
{
    LinkedNode *first;
    int size;
};

void addFirst(SLList *LL, int x)
{
    LinkedNode *newFirst;
    newFirst = createNode(x);
    newFirst->next = LL->first;
    LL->first = newFirst;
    LL->size++;
}
int getFirst(SLList *LL)
{
    if (LL->first != NULL)
        return LL->first->val;
    return 0;
}
int getSize(SLList *LL)
{
    return LL->size;
}
void printSLList(SLList *LL)
{
    LinkedNode *curr = LL->first;
    printf("size : % d, firstVal : % d, allVals: ", getSize(LL), getFirst(LL));
    while (curr != NULL)
    {
        printf("%d->", curr->val);
        curr = curr->next;
    }
    printf("END\n");
}

void deleteNode(SLList *LL, int val)
{
    LinkedNode *curr = LL->first, *prev = NULL;
    while (curr)
    {
        if (curr->val == val)
        {
            if (!prev)
            {
                LL->first = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int main()
{
    SLList myLL = {NULL, 0};
    printSLList(&myLL);

    addFirst(&myLL, 10);
    printSLList(&myLL);

    addFirst(&myLL, 20);
    printSLList(&myLL);

    addFirst(&myLL, 30);
    printSLList(&myLL);

    deleteNode(&myLL, 20);
    printSLList(&myLL);

    deleteNode(&myLL, 30);
    printSLList(&myLL);
}
