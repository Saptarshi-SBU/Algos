/*---------------------------------------------------------------------------------------
 *
 * Max concurrent overlapping intervals
 *
 * g++ -std=c++11 -DDEBUG -o calls concurrent_calls.cpp
 *
 *--------------------------------------------------------------------------------------*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct interval {
	int start_;
	int end_;
};

int main(void) {

	unsigned long max_conc;

	vector<struct interval> interval_vector {{9, 11}, {8, 10}, {7, 10}, {11, 23}};

	sort(interval_vector.begin(), 
	     interval_vector.end(), 
	     [](struct interval p, struct interval q) { return p.start_ < q.start_;});

	#if DEBUG	
	
	for (auto iter : interval_vector) {
		cout << iter.start_ << "--" << iter.end_ << endl;
	}

	#endif

	vector<struct interval> heap_vector;

	for (auto iter : interval_vector) {

		while (heap_vector.size() > 0) {

			pop_heap(heap_vector.begin(), 
				 heap_vector.end(), 
				 [](struct interval p, struct interval q) {return p.end_ >= q.end_;});

			auto item = heap_vector.back();

			if ((iter.end_ <= item.end_) || (iter.start_ <= item.end_)) {
				break;
			} else {
				heap_vector.pop_back();
				continue;
			}
		}

		heap_vector.push_back(iter);

		make_heap(heap_vector.begin(), 
			  heap_vector.end(), 
		 	  [](struct interval p, struct interval q) {return p.end_ >= q.end_;}
			  );
		#if DEBUG

		for (auto iter : heap_vector) {
			cout << iter.start_ << "--" << iter.end_ << endl;
		}

		#endif

		max_conc = std::max(max_conc, heap_vector.size());
	}

	cout << "Max concurrent " << max_conc << endl; 
			
	return 0;
}
