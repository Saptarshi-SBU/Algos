#include <stdio.h>
#include <string.h>

char ch[64];

int fn(int n) {
	int q;
	int a = (n > 0) ? n : -n;

	int i = 0;
	int k = 0;

	while (a) {
		q = a % 2;
		ch[i++] = q ? '1' : '0';
		a = a/2;
	};

	if (n > 0)
		ch[i] = '1';
	else
		ch[i] = '0';

	printf("[%d] ", n);
	for (k = i; k >= 0; k--)
		printf("%c",ch[k]);
	printf("\n");
	
	return 0;
}

int main(void) {
	int i = -100;
	for (;i <= 0; i++)
		fn(i);
	return 0;
}
