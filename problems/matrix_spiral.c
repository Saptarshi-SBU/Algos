/*--------------------------------------------------------------------
 *
 *
 * print matrix spiral
 *
 *
 * ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

enum PATH {
	HORIZONTAL,
	VERTICAL,
};

const int n = 4;	

int arr[][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
//int arr[][3] = { {1, 2, 3}, {5, 6, 7}, {9, 10, 11} };
//int arr[][2] = { {1, 2}, {5, 6} };

void
print_spiral(int arr[][n], int k, int n) {

	int i,j;

	if (k >= n)
		return;

	for(i = k; i < n; i++)
		printf("%d ", arr[k][i]);
	
	for(i = k + 1; i < n; i++)
		printf("%d ", arr[i][n - 1]);

	for(i = n - 2; i >= k; i--)
		printf("%d ", arr[n - 1][i]);
	
	for(i = n - 2; i > k; i--)
		printf("%d ", arr[i][k]);

	printf("\n");
	print_spiral(arr, k + 1, n - 1);
}

int main(void) {
	print_spiral(arr, 0, n);
	return 0;
}
