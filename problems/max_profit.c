/*----------------------------------------------------------------------
 *
 * Trading : max profit
 *
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//int array[] = {100, 180, 260, 310, 40, 535, 695};
int array[] = {1, 100, 180, 1000,  260, 310, 40, 535, 695};
//int array[] = {1000, 100, 80, 10,  2};

#define SIZE(array) sizeof(array)/sizeof(array[0])

void max_trade(int arr[], int size) {

	int i = 0;
	int maxp = 0;
	int max_profit = 0;

	int buy_day  = -1;
	int sell_day = -1;
	

	for (i = size - 1; i >= 0; i--) {
		if (arr[i] >= maxp) {
			if (buy_day != -1) {
				printf("%d : %d\n", buy_day, sell_day);
				max_profit = 0;
				buy_day = -1;
			}
			maxp = arr[i];
			sell_day = i;
			max_profit = 0;
		} else {
			if (max_profit < (maxp - arr[i])) {
				buy_day = i;
				max_profit = maxp - arr[i];
			}
		}
	}

	if (buy_day != -1) {
		printf("%d : %d\n", buy_day, sell_day);
	}

}

// single transaction
void max_profit(int arr[], int size, int* buy, int* sell) {

	int i = 0;
	int maxp = size - 1;
	int max_delta = 0;
	int diff = 0;

	*buy = *sell = -1;

	for (i = size - 1; i>=0; i--)  {
		if (arr[maxp] < arr[i]) {
			maxp = i;
		} else {
			diff = arr[maxp] - arr[i];
			if (max_delta < diff) {
				max_delta = diff;
				*buy  = i;
				*sell = maxp;
			}
		}
	}

}


int main(void) {

	int buy  = -1;
	int sell = -1;
	max_trade(array, SIZE(array));
	max_profit(array, SIZE(array), &buy, &sell);
	printf("max trading profit : %d : %d\n", buy, sell);
	return 0;
}
	 
