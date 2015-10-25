#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
#define EFAIL -1

//int a[] = {-2, 0, 0, 1, 2, 3, 5, 6};
//int b[] = {0, 4, 7, 9, 10, 11, 12};

int a[] = {5, 9, 19, 23, 30, 32};
int b[] ={1, 7, 17, 84};

void print_arrays(void) {
	int i;

	for (i=0; i< ARRAY_SIZE(a); i++) 
		printf("%d ", a[i]);

	printf ("\n");

	for (i=0; i< ARRAY_SIZE(b); i++) 
		printf("%d ", b[i]);

	printf ("\n");
}

int calc_median(int m1, int m2, size_t sample_size) {

	if (!(sample_size % 2)) {
		return (m1 + m2)/2;
	} else {
		return m2;
	}
}

int search(int arr[], int start, int end, int key) {

	int mid;

	// Handle Special Cases
	
	if (key < arr[start]) {
		return 0;
	}

	if (key > arr[end]) {
		return end + 1; 
	}

	mid = start + (end - start)/2;

	//printf("%d\n", arr[mid]);

	if ((arr[mid] <= key) && (arr[mid+1] > key)) {
		return mid + 1;		
	}

	if (key < arr[mid]) 
		return search(arr, start, mid-1, key);

	if (key >= arr[mid]) 
		return search(arr, mid+1, end, key);
}

int __findKth(int m[], int m_start, int m_end, int n[], int n_start, int n_end, int k) {

	int mid, rank, key;
	
	if (k == 1) {
		return m[0] < n[0] ? m[0] : n[0];
	} 

	if (k == 2) {
		return m[0] > n[0] ? m[0] : n[0];
	}

	if (m_start > m_end) {
		return EFAIL;
	}

	mid = m_start + (m_end - m_start)/2;

	key = m[mid];

	rank = mid + search(n, n_start, n_end, key) + 1;

	//printf("val :%d rank :%d start :%d end :%d\n", m[mid], rank, m_start, m_end);

	//sleep(2);

	if (rank > k) {

		return __findKth(m, m_start, mid - 1, n, n_start, n_end, k);

	} else if (rank < k) {

		return __findKth(m, mid + 1, m_end, n, n_start, n_end, k);

	} else {
		return m[mid];
	}
}

int findKth(int k) {
	int ret;

	ret = __findKth(a, 0, ARRAY_SIZE(a)-1, b, 0, ARRAY_SIZE(b)-1, k);
	if (ret != EFAIL) {
		return ret;
	}
		
	ret = __findKth(b, 0, ARRAY_SIZE(b)-1, a, 0, ARRAY_SIZE(a)-1, k);
	if (ret != EFAIL) {
		return ret;
	}

	return ret;

}

// Complexity : O(log(m+n))

int main(int argc, char **argv) {
	int k;
	size_t size;

	k = atoi(argv[1]);
	size = ARRAY_SIZE(a) + ARRAY_SIZE(b);

	//print_arrays();
	//printf ("kth : k :%d val :%d\n", size/2, findKth(size/2));
	//printf ("kth : k :%d val :%d\n", size/2 + 1, findKth(size/2 + 1));
	
	printf("Median : %d\n", calc_median(findKth(size/2), findKth(size/2 + 1), size));
	return 0;
}
