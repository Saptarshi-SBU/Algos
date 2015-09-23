#include <stdio.h>

#define RED 0
#define BLACK 1
#define GREEN 2

int array[] = {0,1,1,1,1,0,1,0,1,2,0,2,2,1,0,0,1,1,2,2,2,2,0,0,0,1};

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

int swap(int *a, int *b) {
	int sum = *a + *b;
	*a = sum - *a;
	*b = sum - *b;
	return 0;
}

int main(void) {
	
	int i = 0;
	int red = 0;
	int green = ARRAY_SIZE(array) - 1;

	while (red < green) {
	 start:
		if (RED == array[i]) {
			if (i == red) {
				i++;
			} else if (array[i] != array[red]) {
				swap(&array[i], &array[red]);
			}
			//inc red partition 
			red++;
		} else if (GREEN == array[i]) {
			// partion complete
			if (i > green) {
				break;
			} else if (array[i] != array[green]) {
				swap(&array[i], &array[green]);
			}
			//inc green parition
			green--;
		} else if (BLACK == array[i]){
			// inc next
			i++;
		} else {
			printf ("invalid element :%d\n", array[i]);
			goto exit; 
		}
	};

	for ( i = 0; i < ARRAY_SIZE(array) ;i++) {
		printf ("%d\n", array[i]);
	}
exit:
	return 0;
}


