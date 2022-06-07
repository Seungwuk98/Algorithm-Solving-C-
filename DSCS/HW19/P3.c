#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMS 10

void InsertionSortReverse(char list[]);
int main(int argc, char* argv[])
{
  char chars[MAX_NUMS]; //List of characters to be sorted

  if (argc < MAX_NUMS){
    printf("Please give %d inputs\n", MAX_NUMS);
    return -1;
  }
  

  for (int index=0; index < MAX_NUMS; index++)
  {
    chars[index] = argv[index + 1][0];    
  }

  InsertionSortReverse(chars); //Call sorting routine

  //Print sorted list  
  for (int index = 0; index < MAX_NUMS; index++)
    printf("%c", chars[index]);

  return 0;
}
/* Do not modify above*/
_Bool compare(char, char);

void InsertionSortReverse(char list[])
{
  for (int i=1; i<MAX_NUMS; ++i) {
    char p = list[i]; int j = i-1;
    while (j >= 0 && compare(p, list[j])) list[j+1] = list[j--];
    list[j+1] = p;
  }
}

_Bool compare(char x, char y) {
  char X = x <= 'Z' ? x + 32 : x;
  char Y = y <= 'Z' ? y + 32 : y;
  if (X == Y) return x < y;
  return X > Y;
}
