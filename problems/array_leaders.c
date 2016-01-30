/*---------------------------------------------------------------------------
 *
 *  leaders in an array
 *
 *
 *  -------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int arr[] = { 100, 200, 50 ,10};

#define SIZE(x) sizeof(x)/sizeof(x[0])

int leaders(int arr[], size_t size) {

	int i = 0;
	int max = INT_MIN;

	for (i = size - 1; i >= 0; i--) {
		if (max < arr[i])  {
			max = arr[i];
			printf ("%d ", max);
		}
	}

	return 0;
}

int main(void) {

	leaders(arr, SIZE(arr));
	return 0;
}
