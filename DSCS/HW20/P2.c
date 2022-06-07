#include <stdio.h> 

int main(int argc, char *argv[]){
    char *input_filename = argv[1]; // name of input file
    // YOUR CODE HERE
    FILE *input_file = fopen(input_filename, "r");
    int c;
    while (fscanf(input_file, "%d", &c) != EOF) printf("%d",c);
    
    return 0; 
}