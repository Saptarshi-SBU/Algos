/*----------------------------------------------------------
 *
 * swap odd and even bits
 *
 * --------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

unsigned int swap_oddeven(unsigned int n) {

	int even_mask = 0xaaaaaaaa;
	int odd_mask  = 0x55555555;

	return (((n & even_mask) >> 1) | ((n & odd_mask) << 1));
}

void bin(unsigned int n) {

	if (!n) {
		printf("\n");
		return;
	}

	bin(n/2);
	printf("%d", n % 2);
	return;
}

int main(void) {

	int n = 0xaaaaaaaa;
	bin(n);
	bin(swap_oddeven(n));
	printf("\n");
	return 0;
}
