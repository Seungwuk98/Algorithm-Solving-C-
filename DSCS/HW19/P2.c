#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10

char *SwitchCase(char *s);
int main(int argc, char* argv[]) {
  char *str; //List of characters to be sorted

  str = argv[1];
  printf("%s", SwitchCase(str));

  return 0;
}
/* Do not modify above */

char *SwitchCase(char *s) {
  for (int i=0; s[i] != '\0'; ++i) {
    s[i] = s[i] <= 'Z' ? s[i] + 32 : s[i] - 32;
  }
  return s;
}