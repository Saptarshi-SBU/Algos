/*--------------------------------------------------------------------

  Program to compute modulo by a power of two
  
  --------------------------------------------------------------------*/
#include <stdio.h>

int mod2(int n) {
    return (n & 0x01) ? 1 : 0;
} 

int main() {
    for (int n = 0; n < 20; n++)
	    printf("Module 2 of %d is %d\n", n, mod2(n));
	return 0;
}
