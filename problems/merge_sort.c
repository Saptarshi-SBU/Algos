#include <stdio.h>
#include <stdlib.h>

#define SIZE(x) sizeof(x)/sizeof(x[0]) 

void 
swap(int *a, int *b) {

	int sum = *a + *b;
	*a = sum - *a;
	*b = sum - *b;
}

void
print(int array[], int size) {
	int i = 0;
	
	for (i = 0; i < size ; i++) 
		printf(" %d ", array[i]);
	printf("\n");
}

int 
merge(int array[], int lo, int high) {

	int i,p,q,j, k;

	int *lp = 0;

	int *rp = 0;

	int mid = (lo + high )/2;

	lp = (int *)malloc(mid - lo + 1);
	rp = (int *)malloc(high - mid);

	for (p = 0, i = lo; i <= mid; p++, i++) {
		lp[p] = array[i];
	}

	for (q = 0, i = mid + 1; i <=high; q++, i++) {
		rp[q] = array[i];
	}

	i = lo;
	j = k = 0;
	while (i <= high) {

		if (j < p && k < q) {

			if (lp[j] > rp[k]) {
				array[i++] = rp[k++];

			} else if (lp[j] < rp[k]) {
				array[i++] = lp[j++];

			} else {
				array[i++] = lp[j++];
				array[i++] = rp[k++];
			} 

		} else if (j < p) {

			array[i++] = lp[j++];

		} else if (k < q) {

			array[i++] = rp[k++];

		} else {

			abort();
		}
			
	};

	free(lp);
	free(rp);

	return 0;
}

int 
merge_sort(int array[], int lo, int high) {

	if (lo == high) {
		return 0;
	}

	int mid = (lo + high)/2;

	merge_sort(array, lo, mid);
	merge_sort(array, mid + 1 , high);
	merge (array, lo, high);
	return 0;
}

int main(void) {

	int array[] = { 100, 1,0, 4, 3, 8, -1};
	printf(" Input Array :\n");
	print(array, SIZE(array));
	merge_sort(array, 0, SIZE(array) - 1);
	printf(" Sorted Array :\n");
	print(array, SIZE(array));
	return 0;
}
