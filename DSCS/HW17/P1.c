/* Description
 * Write a program that reads a positive integer from the keyboard 
 * and displays a 1 if it is divisible by 3 or a 0 otherwise
 */

#include <stdio.h>
#include <stdlib.h>

int main(void){
	// Variable for saving input argument. (a positive integer) 
	int input_int;
	// Variable for answer value 
	int ans = -1;

	/* Please write your code below */
	printf("Enter any natural number:");
	scanf("%d", &input_int);
	ans = input_int%3 ? 0 : 1;
	/* Do not modify below */

	printf("ans:%d\n", ans);

	return 0;
}

