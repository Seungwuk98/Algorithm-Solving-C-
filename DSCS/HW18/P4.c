#include <stdio.h>
#include <stdlib.h>

int P4(int n);
int gcd(int a, int b){
    return a? gcd(b%a, a) : b;
}
int lcm(int a, int b) {
    return a*b/gcd(a, b);
}

int P4(int n){
    int ret = 1;
    for (int i=2; i<=n; ++i) ret = lcm(ret, i);
    return ret;
}

// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P4(n);

    printf("%d\n", ans);


    return 0;
}