#include <stdio.h>
#include <stdlib.h>

/* Linked list node structure */
struct Node {
    int data;
    struct Node* next;
};

/* Function to create a new node */
struct Node * createNode(struct Node * newNode, int data){
  newNode = (struct Node *) malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}


int main(int argc, char* argv[])
{  
  int length = argc - 1;

  /* Create a linked list from input integers */
  int k = 1;
  struct Node * head = NULL;
  struct Node * prev = NULL;
  struct Node * curr = NULL;

addNode:
  curr = createNode(curr, atoi(argv[k]));  
    
  if (k > 1)
    prev->next = curr;
  else
    head = curr;

  k++;
  prev = curr;

  // If there are more nodes left, go back to 'addNode' and execute the codes below again
  if (k <= length)
    goto addNode;

  /* 
   * TODO: Your code starts here
   */	

  prev = head;
  curr = head->next;
  head = NULL;
  while (curr) {
    prev->next = head;
    head = prev;
    prev = curr;
    curr = curr->next;
  }
  prev->next = head;
  head = prev;

	/* 
   * Do not modify below 
   */	


  /* Pinrt reversed linked list */
  curr = head;

  while (curr){
    printf("%d", curr->data);
    curr = curr->next;
  }

  return 0;


}


