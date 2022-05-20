#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main() {
    int num = 54;
    for (int i=2; i<=num; ++i) {
        int k = 0;
        while (!(num%i)) {
            num/=i;
            k++;
        }
        if (k) printf("(%d, %d)", i, k);
    }

}