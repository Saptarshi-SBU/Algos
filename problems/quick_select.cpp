/*----------------------------------------------------------------
  
  Quick Select Algorithm
  Dated : 02/05/2016
-----------------------------------------------------------------*/
#include <iostream>
using namespace std;

#define SIZE(x) sizeof(x)/sizeof(x[0])

void swap(int *a, int *b) {
    
   if (*a == *b)
    return;
    
   *a = *a + *b;
   *b = *a - *b;
   *a = *a - *b;
    return;
    
}

int partition(int array[], int low, int high) {
    
    int pivot = array[high];
    int p = low;
    int q = high - 1;
    
    while (p < q) {
        if (array[p] <= pivot) {
            p++;
        } else if (array[p] > pivot) {
            swap(&array[p], &array[q]);
            q--;
        }	   	
    }
   
    if (pivot < array[p]) {
    	swap(&array[high], &array[p]);
	return p;
    } else {	 
    	return high;
    }	
}

int quick_select(int array[], int low, int high, const int k) {
    
    int p = partition(array, low, high);
    
    if (p == k) {
        return array[p];
    } else if (p < k) {
        return quick_select(array, p + 1, high, k);
    } else {
        return quick_select(array, low, p - 1, k);
    }   
}

int main() {
    //int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    //int array[] = {4, 1, 2, 3, 5, 6, 7, 8};
    int array[] = {4, 3, 7, 1, 2, 5, 6, 8, 0};

    for (int i = 0; i < SIZE(array); i++)
	cout << array[i] << " ";
    cout << endl;
		
    int k, r;
    cout << "Enter index " << endl;	
    cin >> k;

    if ((k >= 0) && (k < SIZE(array))) {
    	r = quick_select(array, 0, SIZE(array) - 1, k);
   	cout << k << "th index " << r << endl;
    } else {
	cout << "invalid Index\n" << endl;
    }	

    for (int i = 0; i < SIZE(array); i++)
	cout << array[i] << " ";
    cout << endl;
		
    return 0;
}
