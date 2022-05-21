/* Description
 * Write a fibonacci function to calculate as following:
 * f(n) = f(n-1) + f(n-2)
 * with f(0) = 1, f(1) = 1
 */

#include <stdio.h>
#include <stdlib.h>


int fibonacci(int n){
/* Please write your code below */	
	if (n == 0 || n == 1) return 1;
	int a = 1, b = 1;
	for (int i=n-1; i--;){
		int tmp = b;
		b = a + b;
		a = tmp;
	}
	return b;
/* Do not modify below */
}


int main(int argc, char* argv[]){

	/* 
	argc: Store the number of arguments of program. 
	argv[]: Array for storing arguments of program. 
	The first value of argv[] is the name of program. 
	That is, if there is no argument, argc is 1 and argv[0] is the name of program. 
	*/

	// If the number of argument is not 1
	if (argc != 2){
		printf("Enter any natural number n\n");
		return 0;
	}

	// Store first argument into variable n
	int n = atoi(argv[1]);		
	// If n is smaller than 0
	if (n < 0){

		printf("No negative number is allowed\n");
		return 0;

	} else {
		// Variable for Storing fibonacci value
		int f = 0;
		// Execute fibonacci function. Then store the result into variable f
		f = fibonacci(n);
		// Print answer 
		printf("%d\n",f);
		return 0;

	}

	
}

