#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

// Print min within a window
#if 0
int main(void) {
	int arr[] = {10,20,30,50,10,70,30};
	int i = 0;
	int j = 0;
	int min = 0;
	
	for ( i= 0; i < ARRAY_SIZE(arr); i++) {
		min = arr[i];
		for (j = 0; j < ARRAY_SIZE(arr) - i; j++) {
			if (min > arr[i + j]) 
				min = arr[i + j];
			printf (" start %d : win %d : min %d\n", i, j + 1, min);		
		
		}
	}
	return 0;
}
#endif

//Print Max of Minimum
int main(void) {
	int arr[] = {10,20,30,50,10,70,30};
	int i = 0;
	int j = 0;
	int k = 0;
	int w = 0;
	int min, max;

	for (w = 0; w < ARRAY_SIZE(arr); w++) {
		max = 0;
		for ( i= 0; i < ARRAY_SIZE(arr) - w; i++) {
			min = arr[i];
			for ( k=1; k <= w; k++) {
				if (min > arr[i+ k]) {
					min = arr[i + k];
				}
			}
			if (max < min) {
				max = min;
			}
		}
		printf("%d\n", max);
	}
	return 0;
}
//http://www.quora.com/How-do-I-solve-the-MBEEWALK-question-on-SPOJ
