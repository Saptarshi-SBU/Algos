/*--------------------------------------------------------------------------------
 *
 *
 *  max product subarray
 *
 *
 *
 * ------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int arr[] = {-2, 10, 1, 4,  2, -2};

#define SIZE(x)	sizeof(x)/sizeof(x[0])

#define max(a, b) (a > b ? a : b)

long int max_product_subarray(int arr[], size_t size) {

	long int maxp = INT_MIN;

	long int rp, rm;

	rp = rm = 0;
	
	int i;

	for (i = 0; i < size; i++) {
		
		if (0 == arr[i]) {
			rm = rp = 0;
		} else if (arr[i] < 0) {
			rp = 0;
			rm = rm ? rm*arr[i] : arr[i];
		} else {
			rp = rp ? rp*arr[i] : arr[i];
			rm = rm ? rm*arr[i] : arr[i];
		}
		maxp = max(maxp, max(rp, rm));
        }        

	return maxp;
}

int main(void) {

	printf("Max product array :%ld\n", max_product_subarray(arr, SIZE(arr)));
	return 0;
}
