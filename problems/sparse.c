/*--------------------------------------------------------------------
 *
 *
 *	sparse number
 *
 *
 * ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int isSparse(int n) {

	while (n) {
		if (0x03 == (n & 0x03))
			return 0;
		n = n >> 1;
        }

	return 1;
}

int main(int argc, char **argv) {

	if (argc < 2)
		return 0;

	int n = atoi(argv[1]);
	while (!isSparse(n))
		n++;

	printf("Sparse number :%d\n", n);
	return 0;
}
