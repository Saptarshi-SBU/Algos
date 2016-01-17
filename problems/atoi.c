/*----------------------------------------------------------------
 *
 *
 *  atoi
 *
 *  -------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_digit(char *p) {

	if (*p >= '0' && *p <= '9')
		return 1;
	else
		return 0;
}

int _atoi(char p[]) {

	long int sum  = 0;
	int sign = 1;

	if (*p == '-') {
	   sign = -1;
	   p++;
	}	
	
	while (is_digit(p)) {
	   sum*=10;
           int val = (*p - '0');
           if ((LONG_MAX - sum) >= val)
		sum+=val;
	   else {
		printf("Overflow!\n");
		break;
	   }

	   p++;	
	};

	if (*p != '\0')
		return 0;
	else
		return sum * sign;
}

int main(int argc, char **argv) {

	if (argc != 2)
		return -1;

	printf("%d\n", _atoi(argv[1]));
	return 0;
}
