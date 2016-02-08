/*-------------------------------------------------------------------------
 *
 *  stack operations
 *
 *  -----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 50

int array[SIZE];

int min_array[SIZE];

int top = 0;
int min = INT_MAX;

int push(int data) {

	// Full
	if (top == SIZE - 1)
		return -1;

	top++;
	array[top] = data;	
	if (data < min)
		min = data;
	min_array[top] = min;
	return 0;
}

int pop(void) {

	if (!top)
		return -1;

	int data = array[top];
	top--; 
	return data;
}

int min_val(void) {

	if (!top)
		return -1;
	return min_array[top];
}

int main(void) {
	int i;
	push(100000);
	push(10000);
	push(1000);
	push(100);
	push(10);
	for (i = 0; i < 10; i++)
		printf("%d : %d\n", pop(), min_val());
	return 0;
}

