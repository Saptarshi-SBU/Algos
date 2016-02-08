/*----------------------------------------------------------------------------
 *
 *  stacks using array
 *
 *  --------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

#define NUM_STACKS 3

int array[SIZE];

int top[NUM_STACKS];
int base[NUM_STACKS];
int *limit[NUM_STACKS];

int stack_init(void) {

	base[0] = top[0] = 0;
	base[1] = top[1] = SIZE - 1;
	base[2] = top[2] = SIZE/2;

	limit[0] = &base[2];
	limit[1] = &top[2];
	limit[2] = &top[1];
}

int push(int data, int stackid) {
	int delta = 0;

	if (stackid >= NUM_STACKS)
		return -1;

	switch(stackid) {

	case 0:
	case 2:
		delta = *limit[stackid] - top[stackid];
	//	printf("%d : %d : %d\n", delta, limit[stackid], top[stackid]);
		if (delta > 0) 
			array[++top[stackid]] = data;
		break;
	case 1:
		delta = top[stackid] - *limit[stackid];
		if (delta > 0) 
			array[--top[stackid]] = data;
		break;
	}

	return (delta > 0) ? 0  : -1;
}

int pop(int stackid) {

	int delta = -1;
	int data  = -1;

	if (stackid >= NUM_STACKS)
		return -1;
	

	switch(stackid) {

	case 0:
	case 2:
		delta = top[stackid] - base[stackid];
		if (delta > 0) {
			data = top[stackid];
			top[stackid]--;
		}
		break;

	case 1:
		delta = base[stackid] - top[stackid];
		if (delta > 0) {
			data = top[stackid];
			top[stackid]++;
		}
		break;
	}

	return data;
}

int main(void) {
	int i = 0;
	stack_init();
	for (i = 0; i < 20; i++)
		printf("%d : %d : %d\n", i, push(i, 0), top[0]);
	for (i = 0; i < 20; i++)
		printf("%d : %d : %d\n", i, push(i, 1), top[1]);
	for (i = 0; i < 20; i++)
		printf("%d : %d : %d\n", i, push(i, 2), top[2]);

	printf("%d\n", pop(0));
	printf("%d\n", pop(1));
	printf("%d\n", pop(2));
	return 0;
}
