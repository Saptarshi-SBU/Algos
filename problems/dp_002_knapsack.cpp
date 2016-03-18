/*------------------------------------------------------------------------------------
 *
 * knapsack problem
 *
 * The iterations can be conducted for each no of items included, whats the max value
 *
		// I will keep this as a reminder of the mistake that a single
		// entry was a combination of n items; and i was building on 
		// top of that. The idea should have been for a single weight,
		// array should be built on incremental items.
		// vtable_.at(w) =  vtable_.at(w - 1); // init
   Date : 03/20/2016	
 * -----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int max_value(vector<pair<int, int >> pv, int w) {

	int n_items_  = pv.size();
	int capacity_ = w;

	if (pv.empty())
	  return 0;

	vector<vector<int> > table_(n_items_ + 1, vector<int> (capacity_ + 1));	

	for (int i = 1; i <= n_items_; i++) {

		for (int w = 1; w <= capacity_; w++) {

		     pair<int, int> s = pv.at(i - 1);	

		     int p = s.first;   
                     int q = s.second;  
		
                     if ((w - p) < 0) {	// exclude
			table_.at(i).at(w) =  table_.at(i - 1).at(w);  // was a confusion whether tab1e[i][w-1]; coz pre-decessor is table[i-1[w]
			continue;
		     } else {
			table_.at(i).at(w) =  max(table_.at(i - 1).at(w), table_.at(i - 1).at(w - p) + q);
		     }   		

		}

	}
	
	for (auto i : table_) {
		for (auto k : i)
			cout << k << " " ;
		cout << endl;
	}

	return table_.at(n_items_ ).at(capacity_);
}

int main(void) {

	vector<pair<int, int>> v;

	v.push_back(pair<int, int> (1, 8));
	v.push_back(pair<int, int> (2, 4));
	v.push_back(pair<int, int> (3, 0));
	v.push_back(pair<int, int> (2, 5));
	v.push_back(pair<int, int> (2, 3));

	cout << "Weight " << "\t" << "Value" << endl;
	cout << "-----------------------------------" << endl;
	for (auto i : v)
		cout << i.first << "\t" << i.second << endl;

	cout << "Weight " << "\t" << "KnapSackValue" << endl;
	cout << "-----------------------------------" << endl;
	int ans = max_value(v, 4);
	cout << "------Result------------" << endl;
	cout << ans << endl;

	return 0;
}
