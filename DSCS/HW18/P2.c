#include <stdio.h>
#include <stdlib.h>

int P2(int n); // 함수 선언

// Implement P2 
// You can define other function, but P2 must return answer.

int P2(int n){ // 합수 정의
    // write your code below
    int ret = 0;
    while (n) {
        ret += n%10;
        n/=10;
    }
    return ret;
}


// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P2(n);

    printf("%d\n", ans);

    return 0;
}