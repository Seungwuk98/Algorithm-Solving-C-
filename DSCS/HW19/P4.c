#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN 10

void print_dup_numbers(int* numbers, int n_integers);

int main(int argc, char* argv[]) {
    if (argc == 1) {
      printf("Please input at least 1 integer.\n");
    }

    int numbers[MAX_LEN];
    for (int i = 1; i < argc; ++i) {
        int tmp = atoi(argv[i]);
        numbers[i-1] = tmp;
    }
    print_dup_numbers(numbers, argc-1);

    return 0;
}
/* Do not modify above*/

void print_dup_numbers(int* numbers, int n_integers) {
    int c = 0;
    int check[10];
    for (int i=0; i<n_integers; ++i) {
        for (int j=i+1; j<n_integers; ++j) if (i != j && numbers[i] == numbers[j]) {
            _Bool dup = 1;
            for (int k=0; k<c; ++k) {
                if (numbers[i] == check[k]) {
                    dup = 0; break;
                }
            }
            if (dup) {
                printf("%d", numbers[i]);
                check[c++] = numbers[i];
            }
        }
    }
    if (c == 0) printf("-1");
}