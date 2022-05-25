#include <stdio.h>
#include <stdlib.h>

int P1(int n); // 함수 선언
int hanoi(int num, int from, int to, int support);

// Implement P1 
// You can define other function, but P1 must return answer.



int P1(int n){ // 함수 정의
    return hanoi(n, n, 0, 0);
}

int hanoi(int num, int from, int to, int support) {
    if (num <= 1) return num;
    int ret = 0;
    ret += hanoi(num-1, from, support, to);
    ret++;
    ret += hanoi(num-1, support, to, from);
    return ret;
}



// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){ //argc: 입력된 문자열 개수, argc: 입력된 문자열
    int n = atoi(argv[1]); //atoi: 입력된 문자열을 정수로 변환
    int ans = P1(n);

    printf("%d\n", ans);

    return 0;
}