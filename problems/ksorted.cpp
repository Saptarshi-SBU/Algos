/*-------------------------------------------------------------------------------
 *
 * k sorted array using heap
 *
 * g++ -std=c++11 -o ksorted ksorted.cpp
 * ------------------------------------------------------------------------------*/

#define EOK 0
#define EFULL -1
#define EINVAL -2

#define SIZE(x) sizeof(x)/sizeof(x[0])

#include <iostream>
#include <cmath>

static 
void swap(int *m, int *n) {

	int sum = *m + *n;
	*m = sum - *m;
	*n = sum - *n;
}

class Heap {

	private:

		int *root_;
		int capacity_;
		int no_elements_;

	protected:

		int siftup(int index) {

			if (index == 0) 
				return EOK;

			swap(&root_[index], &root_[parent_of(index)]);
			index = parent_of(index);
			if (root_[index] < root_[parent_of(index)])
				siftup(index);
			return EOK;
		}
			
		int siftdown(int index) {

			int i     = 0;
			int left, right; 
			
			if (index > no_elements_ - 1) 
				return -EINVAL;

			left  = leftchild_of(index);
			if (left < 0) 
				return -EINVAL;

			right = rightchild_of(index);
			if (right < 0) {
				if (root_[index] > root_[left]) {
					swap(&root_[index], &root_[left]);
				}
				return EOK;
			}

			if ((root_[index] > root_[left]) || (root_[index] > root_[right])) {
				i = root_[left] < root_[right] ? left : right;
				swap(&root_[index], &root_[i]);
				siftdown(i);
			}

			return EOK;
		}	

		inline int parent_of(int index) {

			if (!index)
				return -1;

			return index/2;
		}


		inline int leftchild_of(int index) {

			int child = 2*index + 1;	
			return child < no_elements_ ? child : -EINVAL;	
		}
			
		inline int rightchild_of(int index) {

			int child = 2*index + 2;	
			return child < no_elements_ ? child : -EINVAL;	
		}
			
	public:
	
		Heap(int array[], int max, int num) : root_(array), capacity_(max), no_elements_(num) {}

	       ~Heap() {}
	
		int heap_size(void) {
			return no_elements_;
		}

		int build_heap(void) {

			int i = 0;

			if (!root_)
				return -EINVAL;

			for ( i = heap_size()/2 ; i >= 0; i--) {
				heapify(i);
			}

			return EOK;
		}

		int heap_sort(void) {

			while (no_elements_ > 0) {
				swap(&root_[0], &root_[no_elements_ - 1]);
				no_elements_--;
				heapify(0);
			}

			return EOK;
		}

		int insert(int item) {

			int index = no_elements_;
			
			if (no_elements_ >= capacity_)  {
				std::cout << "Err : Heap Full!" << std::endl;
				return -EFULL;
			}

			root_[index] = item;
			no_elements_++; 
			if (root_[index] < root_[parent_of(index)])
				siftup(index);
			return EOK;
		}

		int remove(int index) {

			if (index > no_elements_ - 1) 
				return -EINVAL;
			
			swap(&root_[index], &root_[no_elements_ - 1]);
			no_elements_--;
			heapify(index);
			return EOK;
		}
			
		int extract_min(void) {

			int min = root_[0];
			swap(&root_[0], &root_[no_elements_ - 1]);
			no_elements_--;
			heapify(0);
			return min;
		}

		int heapify(int index) {

			if ((root_[leftchild_of(index)] < root_[index]) || (root_[rightchild_of(index)] < root_[index]))
				siftdown(index);
			return EOK;
		}

		void print_heap(void) {
			int i = 0;
			int h = 0;
			int height = log2 (heap_size());

			while (h <= height) {
				int start = pow(2, h) - 1;
				int end   = start + pow(2, h) - 1;

				for ( i = start ; i <= end && i < no_elements_ ; i++)
					std::cout << "[" << i << "]" << root_[i] << "\t";
			
				std::cout << std::endl;
				h++;
			}
		}
};

static void
print_array(int array[], int size) {

	int i;
	
	for (i = 0; i < size; i++) {
		std::cout << array[i] << " \t";
	}

	std::cout << std::endl;
}

#define K 2

int array[] = { -1, 2, 3, 0, 1, 5, 4, 200, 100, 300};

int main(void) {

	int i, j, k;

	auto *p = new int [2*K];
	if (!p)
		return -ENOMEM;

	Heap *heap = new Heap(p, 2*K, 0);

	std::cout << "Input Array " << std::endl;

	print_array(array, SIZE(array));

	i = j = k = 0;

	while ( k < SIZE(array)) { //<-------O(n)
	
		while (i < SIZE(array)) {   
			if (heap->insert(array[i]) == EOK) //<------O(logn)
				i++;
			else 
			    break;
		}

		for (j = 0; j < K ; j++, k++) {
			array[k] = heap->extract_min(); //<------O(1)
		}
	}

	delete heap;

	delete [] p;

	std::cout << "Sorted Array " << std::endl;

	print_array(array, SIZE(array));
	
	return 0;
}
