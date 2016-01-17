/*-------------------------------------------------------------------------
 *
 *
 * Coin Change Problem
 *
 * gcc -g -std=c99 -o cc coin_change.c
 * -----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE(x) sizeof(x)/sizeof(x[0])
#define MAX 50

int coin_list[] = { 1, 5, 10, 25 }; //2, 3, 5, 7, 10 };

int min_sum[MAX];

int count_min(int sum) {

	int min = MAX + 1;

	if (sum < 0)
		return -1;

	if (sum == 0)
		return 0;

	if (min_sum[sum])
		return min_sum[sum];

	for (int i = 0, count = 0; i < SIZE(coin_list); i++, count = 0) {
                 int r = count_min(sum - coin_list[i]);
		 if (r < 0)
			continue;	
		 count = 1 + r;
		 if (min > count)
			min = count;
	}

	if (min == MAX + 1)
		min_sum[sum] = 0;
	else
		min_sum[sum] = min;

	return min_sum[sum];
}

int main(int argc, char **argv) {

	if (argc != 2)
		return -1;

	int sum = atoi(argv[1]);

	if (sum >= MAX)
		return -1;

	printf("Min Change :%d\n", count_min(sum));
	return 0;
}
