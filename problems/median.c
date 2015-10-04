#include <stdio.h>

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
#define MERGE_SIZE(a, b) (ARRAY_SIZE(a) + ARRAY_SIZE(b))

int a[] = {0, 0, 1, 2, 3, 5, 6};
int b[] = {0, 4, 7, 9, 10, 11, 12};

int median(int m1, int m2, size_t size) {
	if (size % 2) {
		return (m1 < m2) ? m1 : m2;
	} else {
		return (m1 + m2)/2;
	}
}

int merge_median02(int a[], int b[], size_t a_size, size_t b_size, int n) {

	int mid_a = a[(a_size - 1)/ 2]; 
	int mid_b = b[(b_size - 1)/ 2]; 

	if (mid_a > mid_b) {
		b+=(b_size/sizeof(int));	
		n+=(b_size/2);
		b_size/=2;
	} else if (mid_a < mid_b) {
		a+=(a_size/sizeof(int));	
		n+=(a_size/2);
		a_size/=2;
	} else {
		return mid_a; // or mid_b
	}

	if (n >= MERGE_SIZE(a, b)/2) {
		return median(mid_a, mid_b, MERGE_SIZE(a, b)/2);
	} else {
		return merge_median02(a, b, a_size, b_size, n);
	}
}

int main(void) {
	printf ("%d\n", merge_median02(a, b, ARRAY_SIZE(a), ARRAY_SIZE(b), 0));
	return 0;
}
