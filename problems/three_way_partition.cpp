/*------------------------------------------------------------------------------
 * Dutch Natinal Flag Program
 * Dated : 28.12.2015
 * gcc -o main main.cpp -Wall -std=gnu++11
 *-----------------------------------------------------------------------------*/
#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

/*
 *
 * 1, 2, 0
 *
 * 0, 2, 1 
 *
 *
 */

enum balls : int {
	RED = 0,
 	GREEN = 1,
	BLACK = 2,
};

static int array[] = {RED, RED, BLACK, BLACK, GREEN, GREEN};

int swap(int *src, int *dst) {
	int sum = *src + *dst;
	*src = sum - *src;
	*dst = sum - *dst;
	return 0;	
}

int three_way_partitioning(void) {

	int curr  = 0;

	int front = 0;
	int rear  = (int) ARRAY_SIZE(array) -  1;

        while (curr < (int) ARRAY_SIZE(array)) {

		switch(array[curr]) {
			case RED :
				if (curr > front) {
					swap(&array[curr], &array[front]);
					front++;
				} else {
					curr++;
				}
				break; 

			case GREEN :
				curr++;
				break;

			case BLACK :
				if (curr < rear) {
					swap(&array[curr], &array[rear]);
					rear--;
				} else {
					curr++;
				}
				break;
		}
	};

	return 0;
}

int print_array(void) {

	int i;
	for (i = 0; i < (int) ARRAY_SIZE(array); i++) {
		printf("[%d] %d\n", i, array[i]);
	}
	return 0;
}

int main(void) {
	printf ("==Before===\n");
	print_array();
	three_way_partitioning();
	printf ("==After===\n");
	print_array();
	return 0;
}
