/*----------------------------------------------------------------------
 *
 * Trading : max profit
 *
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

//int array[] = {100, 180, 260, 310, 40, 535, 695};
//int array[] = {1, 100, 180, 1000,  260, 310, 40, 535, 695};
int array[] = {1000, 100, 80, 10,  2};

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

int main(void) {

	max_trade(array, SIZE(array));
	return 0;
}
	 
