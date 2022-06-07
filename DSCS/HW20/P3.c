#include <stdio.h>

int main(int argc, char *argv[]){    
    char *input_filename = argv[1]; // name of input file
    char *output_filename = argv[2]; // name of output file
    // YOUR CODE HERE
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");
    char str[32];
    int i;
    int num;
    while (fscanf(input_file, "%d", &num) != EOF) {
        i = 0;
        int tnum = num;
        while (tnum) {
            str[i++] = '0' + (tnum&1);
            tnum >>= 1;
        }
        str[i] = '\0';
        for (int j=0, k=i-1; j<k; j++, k--) {
            char tmp = str[j]; str[j] = str[k]; str[k] = tmp;
        }
        fprintf(output_file, "%d = %s\n", num, str);
    }


    return 0;
}
