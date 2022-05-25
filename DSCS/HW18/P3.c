#include <stdio.h>
#include <stdlib.h>

int P3(int n);
_Bool isSelfNumber(int x);

// Implement P4 
// You can define other function, but P4 must return answer.
int P3(int n){
    while (1){
        if (isSelfNumber(++n)) return n;
    }

}

_Bool isSelfNumber(int x) {
    int b = 0;
    for (int i=1; i<=x; i*=10, b++);
    for (int i=x-b*9; i<x; ++i) {
        if (i < 0) continue;
        int ret = i;
        for (int j=i; j; j/=10) ret += j%10;
        if (ret == x) return 0;
    }
    return 1;
}



// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P3(n);

    printf("%d\n", ans);

    return 0;
}