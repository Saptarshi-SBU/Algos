/*----------------------------------------------------------------
 *
 *   quick sort using arrays
 *
 *   gcc -g -o qs quick_sort.c
 *---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define SIZE(x) sizeof(x)/sizeof(x[0]) 

static 
void swap(int *p, int *q) {
	int sum = *p +  *q;
	*p = sum - *p;
	*q = sum - *q;
}

void
print(int array[], int size) {
	int i = 0;
	
	for (i = 0; i < size ; i++) 
		printf(" %d ", array[i]);
	printf("\n");
}

int 
partition(int array[], int lo, int high) {

	int i, l, h;
	int pivot;

	if (lo == high - 1) {
		if (array[lo] > array[high]) 
			swap(&array[high], &array[lo]);
		return high;
	}
		
	i = l = lo;
	h = high - 1;
	pivot = array[high];

	while (l < h) {
		if (array[i] <= pivot) {
			l++;
			i++;
		} else {
			swap(&array[i], &array[h]);
			h--;		 
		}
	};
	
	swap(&array[high], &array[l]);
	return l;
}

int quick_sort(int array[], int lo, int high) {

	if (lo >= high) 
		return 0;

	int p = partition(array, lo, high);
	if (p != lo) 
		quick_sort(array, lo, p-1);
	if (p != high)
		quick_sort(array, p, high);
	return 0;
}

int main(void) {

	int array[] = { 100, 0, 1 ,2 ,4 , -1, 6, 5};
	printf (" Input array \n");
	print(array, SIZE(array));
	quick_sort(array, 0, SIZE(array) - 1);
	printf (" Sorted array \n");
	print(array, SIZE(array));
	return 0;
}
