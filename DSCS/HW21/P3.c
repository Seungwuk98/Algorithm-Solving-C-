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
  /* length: the length of input arguments (except for inputList.txt) */
  int length = argc - 2;
  /* inputArr: array of input arguments (except for inputList.txt) */
  int * inputArr = (int *) malloc(sizeof(int) * length);
  /* filepath: path for inputList.txt which will be give as a first argument */
  char * filepath = argv[1]; 

  /* Create inputArr */
  for (int i = 0; i < length; ++i){
    inputArr[i] = atoi(argv[i+2]);
  }

  /* Create a linked list from file input */
  int k = 1;
  struct Node* head = NULL;
  struct Node* prev = NULL;
  struct Node* curr = NULL;

  FILE *fp = fopen(filepath, "r");
  char buffer[10]; 
  
  while (fscanf(fp, "%s", buffer) == 1){
    curr = createNode(curr, atoi(buffer));  
    if (k > 1){
      prev->next = curr;
    }
    else{
     head = curr;
    }
    k++;
    prev = curr;
  }

  fclose(fp);
  
  /* numConnected: the number of connected "cluster" */
  int numConnected = 0;

  /* 
   * TODO: Your code starts here
   */	
  _Bool * vst = (_Bool *) malloc(sizeof(_Bool) * length);
  for (int i=0; i<length; ++i) parent[i] = 0;
  prev = NULL;
  curr = head;
  while (curr) {
    prev = curr;
    
    curr = curr.next;
  }





	/* 
   * Do not modify below 
   */	

  printf("%d", numConnected);

  return 0;


}


