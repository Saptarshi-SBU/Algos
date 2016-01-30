/*------------------------------------------------------------------------------------------
 *
 *	rotate an array
 *
 * -----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE(x) sizeof(x)/sizeof(x[0])

int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

void reverse(int arr[], int low, int high) {

	int p = low;
	int q = high;
	
	while (p < q) {
		int xor = arr[p]^arr[q];
		arr[p]  = xor^arr[p];
		arr[q]  = xor^arr[q];	
                p++;
                q--;
	}
}

void rotate(int arr[], size_t size, int k, int dir) {

	int p;

	if (dir == 1) 
		p = k % size - 1;
	else 
		p = (size - k) % size - 1;
                
	reverse(arr, 0, size - 1);
	reverse(arr, 0, p);
	reverse(arr, p + 1, size - 1);
}

int main(int argc, char **argv) {

	int i;

	if (argc < 3) 
		return 0;

	int num = atoi(argv[1]);

	int dir = atoi(argv[2]);

	printf("Org Array : ");
	for (i = 0; i < SIZE(arr); i++)
		printf("%d ", arr[i]);

	rotate(arr, SIZE(arr), num, dir);

	printf("\nRotated Array (%d) :", num);
	for (i = 0; i < SIZE(arr); i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}
