/* Description
 * Write a function to return an natural number in base 4
 */

#include <stdio.h>
#include <stdlib.h>

	
int base_four(int n){
/* Please write your code below */
	int ret = 0;
	int c = 1;
	while (n) {
		ret += n%4*c;
		n/=4;
		c*=10;
	}
	return ret;
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

	// If n is smaller than 1
	if (n < 1){

		printf("No negative number is allowed\n");
		return 0;

	} else {

		int f = 0;
		// Execute base_four function. Then store the result into variable f
		f = base_four(n);
		// Print answer
		printf("%d\n",f);	
		return 0;

	}


}

