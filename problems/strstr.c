/*---------------------------------------------------------------------------------
 *
 * strstr
 *
 * implementation using KMP algorithm
 *
 * ./prefix abcabc ddddabcabxabcabc
 * [0] 0
 * [1] 0
 * [2] 0
 * [3] 1
 * [4] 2
 * [5] 3
 * start : 0
 * start : 1
 * start : 2
 * start : 3
 * start : 4
 * start : 8
 * start : 9
 * start : 10
 * Match Found
 *
 * -------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv) {

	if (argc != 3)
		return -1;

	char *pattern = argv[1];

	int len = strlen(pattern);

#if 0
	int index = atoi(argv[2]);

	char *temp = (char*) malloc (index + 1);
	if (!temp)
		return -1;

	for (int i = 0; i < index; i++) {
		temp[i] = pattern[i];
		temp[i + 1] = '\0';
		printf("prefix : %s\n", temp);
	}


	temp[index] = '\0';
	for (int i = 0; i < index; i++) {
		temp[index -i - 1] = pattern[index - i];
		printf("suffix : %s\n", &temp[index - i - 1]);
	}
#endif

	char *p = (char*) malloc (len + 1);
	if (!p)
		return -1;

	char *q = (char*) malloc (len + 1);
	if (!q)
		return -1;

	char *prefix_table = (char*) malloc(len);

	int max;

	for (int k = 0, max = 0; k < len ; k++, max = 0) {

		for (int i = 0; i < k; i++) {

			p[i] = pattern[i];
			p[i + 1] = '\0';

			for (int j = i; j > 0; j--)
				q[j] = q[j - 1];
			q[0] = pattern[k - i];
			q[i + 1] = '\0';

			if (strcmp(p, q) == 0)
				max = i + 1;
			#if DEBUG
			printf("[%d] len = %d : %s %s\n", k, i, p, q);
			#endif
		}

		prefix_table[k] = max;
		printf("[%d] %d\n", k, max);
	}


	char *string = argv[2];

	int i = 0;
	int done  = 0;
        int start = 0;

	//  Pat : ABA
	//  Str : CABA
	//
	while (!done) {
		printf ("new skip start : %d\n", start);
		
		while (pattern[i] != '\0' && string[start + i] != '\0' && pattern[i] == string[start + i]) { 
			i++;
		};

		if (pattern[i] == '\0') {
			done = 1;
		} else if (string[start + i] == '\0') {
			break;
		} else {
			if (prefix_table[i])
				start+=(prefix_table[i] + 1); 
			else
				start++;
			i = 0;
		}
	}
				
	if (done)
		printf("Match Found at :%d\n", start);
	else
		printf("Match Not Found\n");		   

	return 0;
}
