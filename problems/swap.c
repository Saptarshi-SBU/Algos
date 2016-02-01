/*-------------------------------------------------------
 *
 * swap
 *
 * -----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {

	if (*a == *b) 
		return;
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
	return; 
}

int main(void) {

	int a = 10;
	int b = 20;

	printf ("%d : %d\n", a, b);
	swap(&a, &b);
	printf ("%d : %d\n", a, b);
	return 0;
}
