/*---------------------------------------------------------------------------
 *
 *	iterative Merge sort
 *
 *      //revisit
 *--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

void 
swap(int *a, int *b) {

	int sum = *a + *b;
	*a = sum - *a;
	*b = sum - *b;
}

void
print_array(int array[], int size) {
	int i = 0;
	
	for (i = 0; i < size ; i++) 
		printf(" %d ", array[i]);
	printf("\n");
}

int merge(int array[], int l, int h) {

	if (l == h) {
		return 0;

	if (h - l == 1) {
		if (array[l] > array[h]) 
			swap(&array[l], &array[h]);
		return 0;
	}

	int m = (h - l)/2;	

	int *p = (int*) malloc (m - l + 1);
	int *q = (int*) malloc (h - m);

	for (int i = 0, int j = l; i < (m - l + 1); i++, j++) 
		p[i] = array[j];
		
	for (int i = 0, int j = h; i < (h - m); i++, j++) 
		q[i] = array[j];
	
	int i = l;

	int j,k;

	j = k = 0;

	while (i <= h) {

		if ((j < (m - l + 1)) && (k < (h - m)))  {

			if (p[j] < q[k] 
				array[i++] = p[j++];
 			else 
				array[i++] = q[k++];

		} else if ( j < (m - l + 1)) {
			array[i++] = p [j++];
		} else if ( k < (h - m)) {
			array[i++] = j[k++];
		} else {
			abort();
		}
	}

	return 0;
}


int merge_sort(int array[], size_t size) {

	int l, h;
	int levels;

	for (levels = 0 ; levels < max_levels; levels++) {

		level_size = pow(levels, 2);	

		for (l = 0, h = level_size - 1, ; h < size; l+=level_size, h+=level_size) {

			merge(array, l, h);   

		}
	}

	return 0;		 
}

#define SIZE(x) sizeof(x)/sizeof(x[0])

int main(void) {
	
	int array[] = { 9, 4, 2, 5, 1};

	merge_sort(array, SIZE(array));

	print_array(array, SIZE(array));	

	return;
}
