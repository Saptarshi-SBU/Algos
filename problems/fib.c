#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PANIC(str)  printf(str); \
			abort();
 
unsigned long _f(unsigned long curr, unsigned long prev, int n) {

	if (n < 0)
		return curr;

	 if (ULONG_MAX - prev > curr) {
		return _f(curr + prev, curr , --n);
	 } else  {
		PANIC("Overflow!");
	 }
}

unsigned long _f_iter(int n) {

	unsigned long sum = 0;
	unsigned long curr = 1;
	unsigned long prev = 0;

	if (0 == n)
		return 0;
	else if ( 1 == n)
		return 1;

	n = n - 2;

	while (n >= 0) {
	
		if ((ULONG_MAX - prev) > curr)
			sum = curr + prev;
		else {
			PANIC("Overflow!");
		}
		prev = curr;
		curr = sum;
		n--;
	};

	return sum;
}
		

unsigned long f(int n) {

	if (0 == n)
		return 0;
	else if ( 1 == n)
		return 1;
	else 
		return _f(1, 0, n - 2);
}
		
int main(int argc, char **argv) {
	if (argc != 2)
		return -1;
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++)
		printf ("[%d] fibonacci number is :%lu\n", i, _f_iter(i));
		//printf ("[%d] fibonacci number is :%lu\n", i, f(i));
}
