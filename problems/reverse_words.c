#include <stdio.h>
#include <string.h>
#define PRINT(str) printf(str); \
			printf("\n")

int reverse_string(char *str, int len) {

	int i = 0;
	int j = len - 1;
	char ch;

	if ((len <= 0) || !str) {
		return -1;
	}     

	while (i < j) {
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		i++;
		j--;
	};  

	return 1;
}     


int main(int argc, char **argv) {

	int flag = 0;
	int done = 0;

	char *startp_ = 0;
	char *p = argv[1]; 

	if (argc != 2) {
		PRINT("invalid number of arguments");
		return -1;
	}

	if (reverse_string(p, strlen(p)) < 0) {
		PRINT("Invalid string params");
		return -1;
	}    

	while (!done) {

		if ((flag == 0) && (*p != ' ')) {
			startp_ = p;
			flag = 1;
		} else if ((flag == 1) && ((*p == ' ') || (*p == '\0')))  {
			reverse_string(startp_, p - startp_);
			flag = 0;
		}   

		if (*p == '\0')
			done = 1;
		else
			p++;
	};

	printf("\n%s\n", argv[1]);	
} 
