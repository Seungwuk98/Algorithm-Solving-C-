#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

  if (argc < 4){
    printf("Please input at least 4 integers\n");
  }

  int i = atoi(argv[1]);
  int j = atoi(argv[2]);
  int k = atoi(argv[3]);
  int l = atoi(argv[4]);

  char *alphabet[] = {"ABCD", "EFGH", "IJKL", "MNOP"};  

  char a, b, c, d;
    
  /* Write your code here */	
  a = alphabet[i][0];
  b = alphabet[j][1];
  c = alphabet[k][2];
  d = alphabet[l][3];
  /*do not modify below*/

  printf("%c%c%c%c\n", a,b,c,d);
  return 0;
}
