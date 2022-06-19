#include <stdio.h>
#include <stdlib.h>

typedef struct sll_t linkedlist; 
typedef struct node_t node; 


struct node_t
{
    node *next;
    int data;
};

struct sll_t
{
    node *top;
    int size;
};

node *create_node(int data) {
    node *ret = (node *)malloc(sizeof(node));
    ret->next = NULL;
    ret->data = data;
    return ret;
}

linkedlist *create_ll() {
    linkedlist *ll = (linkedlist *)malloc(sizeof(linkedlist));
    ll->size = 0;
    ll->top = NULL;
    return ll;
}

void add_node(linkedlist *ll, int data) {
    node *new_node = create_node(data);
    node *curr = ll->top;
    if (curr) {
        while (curr->next) curr = curr->next;
        curr->next = new_node;
    } else {
        ll->top = new_node;
    }
    ll->size++;
}

void printll(linkedlist *ll) {
    node *curr = ll->top;
    for (int i=0; i<ll->size; ++i, curr=curr->next) {
        printf("-%d",curr->data);
    }    
}

void delete_node(linkedlist *ll, int data) {
    node *curr = ll->top, *prev = NULL;
    while (curr) {
        if (curr->data == data) {
            ll->size--;
            if (prev) {
                prev->next = curr->next;
            } else {
                ll->top = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}


int main()
{
    linkedlist *ll = create_ll();
    for (int i=0; i<10; ++i) {
        add_node(ll, i);
    }
    delete_node(ll, 3);
    delete_node(ll, 4);
    delete_node(ll, 0);
    printll(ll);
} // namespace std;


