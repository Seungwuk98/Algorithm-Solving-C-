#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int N = atoi(argv[1]);
    // YOUR CODE HERE
    int t = N-1;
    for (int i=0; i<t; ++i) printf("%c",' ');
    printf("%c",'*');
    for (int i=0; i<t; ++i) printf("%c",' ');
    int u=1;
    printf("\n");
    for (int i=2; i<N; ++i) {
        t--;
        for (int i=0; i<t; ++i) printf("%c",' ');
        printf("%c", '*');
        for (int i=0; i<u; ++i) printf("%c",' ');
        printf("%c", '*');
        for (int i=0; i<t; ++i) printf("%c",' ');
        printf("\n");
        u+=2;
    }
    if (N > 1) for (int i=0; i<2*N-1; ++i) printf("%c",'*');
    return 0;
}