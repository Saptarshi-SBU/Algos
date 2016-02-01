/*---------------------------------------------------------------------------------------
 *
 *
 *  rotate array search
 *  Date : 01/31/2016
 * -------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE(arr) sizeof(arr)/sizeof(arr[0])

int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void print(int arr[], size_t size) {

	int i;
	for (i = 0; i < size ;i++)
		printf("%d ", arr[i]);
	printf("\n");
}
	
void reverse(int arr[], int low, int high) {
	
	while(low < high) {
		int xor   = arr[low]^arr[high];
		arr[low]  = xor^arr[low];
		arr[high] = xor^arr[high]; 
		low++;
		high--;
	}
}
enum DIR_TYPE {
	CLOCKWISE,
	ACLOCKWISE,
};

void rotate(int arr[], size_t size, int shift, enum DIR_TYPE d) {

	if (ACLOCKWISE == d)
		d = size - d;

	reverse(arr, 0, size - 1);
	reverse(arr, 0, shift-1);
	reverse(arr, shift, size - 1);
} 

int find_pivot(int arr[], size_t size)  {

	int p,q, mid;

	p = 0;
	q = size - 1;

	while (p < q) {
		mid = p + (q - p)/2;
		if (arr[mid] > arr[mid + 1]) {
			break;
		} else if (arr[mid] > arr[q]) {
			p = mid + 1;
		} else if (arr[mid] < arr[p]) {
			q = mid - 1;
		} else {
			mid = -1; // array not sorted
			break;
		}
	}
	
	return mid + 1;
}

int rbsearch(int arr[], size_t size, int key) {
	
	 int p = 0;
	 int q = size - 1;

	 int mid    = -1;
	 int found  =  0;

	 while (p <= q) {
		
		mid  = p + (q - p)/2;

		printf("%d : %d\n", arr[mid], key);

		if (arr[mid] == key) { 

			found = 1;
			break;

	 	} else if (arr[mid] > key) {
			
			if ((arr[mid] > arr[q]) && (key >= arr[q]))
				p = mid + 1;
			else
				q = mid - 1; 

		} else if (arr[mid] < key) {

			if ((arr[mid] < arr[p]) && (key >= arr[p]))
				q = mid - 1;
			else
				p = mid + 1;
		}
	}

	return found;
}

int main(int argc, char **argv) {

	if (argc < 3)
		return -1;

	int shift = atoi(argv[1]);
	int key   = atoi(argv[2]);

	print(arr, SIZE(arr));
	rotate(arr, SIZE(arr), shift, CLOCKWISE);	
	print(arr, SIZE(arr));

	int p = find_pivot(arr, SIZE(arr));
	int ret = rbsearch(arr, SIZE(arr), key);

	printf("shift\t : %d\n", shift);
	printf("key\t : %d\n", key);
	printf("Pivot\t : %d\n", p);
	printf("Found\t: %d\n", ret); 
	
	return 0;
}
