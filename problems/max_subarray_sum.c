/*------------------------------------------------------
 *
 *
 * Max subarray sum
 *
 * ------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int arr[] = {-3, -1, 0};

#define SIZE(x) sizeof(x)/sizeof(x[0])

#define max(a, b) (a > b ? a : b)

long int max_subarray_sum(int arr[], size_t size) {
	
	long int maxs = INT_MIN;

	long int sum = 0;

	int i;

	for (i = 0; i < size; i++) {
		sum = sum + arr[i];
		maxs = max(max(maxs, sum), arr[i]);
		if (sum < 0) 
			sum = 0;
	}

	return maxs;
}

int main(void) {

	printf("Max subarray sum :%ld\n", max_subarray_sum(arr, SIZE(arr)));
	return 0;
}

