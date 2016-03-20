/*------------------------------------------------------------------------------------
 *
 * coin-change problem : variation of combinatorics, number of valid subsets 
 *
 * The iterations can be conducted for each no of items included, whats the max value
 *
   Date : 03/20/2016	
 * -----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

long unsigned max_value(vector<int> pv, int w) {

	int n_coins_  = pv.size();
	int sum_ = w;

	if (pv.empty())
	  return 0;

	vector<vector<long unsigned> > table_(sum_ + 1, vector<long unsigned> (n_coins_ ));	

	for (int i = 0; i < n_coins_; i++)
		table_.at(0).at(i) = 1;
	
	for (int w = 1; w <= sum_; w++) {

		for (int i = 0; i < n_coins_; i++) {

		     int p = pv.at(i);	

                     if ((w - p) < 0) {	
			table_.at(w).at(i) = (i > 0 ? table_.at(w).at(i-1) : 0);
		     } else  {
			table_.at(w).at(i) = (i > 0 ? table_.at(w).at(i-1) : 0) + table_.at(w - p).at(i);
		     }	

		}

	}
#if 1	
	for (auto i : table_) {
		for (auto k : i)
			cout << k << " " ;
		cout << endl;
	}
#endif
	return table_.at(sum_).at(n_coins_ - 1);
}

//245 26
//16 30 9 17 40 13 42 5 25 49 7 23 1 44 4 11 33 12 27 2 38 24 28 32 14 50
int main(void) {

	vector<int> v = {16, 30, 9, 17, 40, 13, 42, 5, 25, 49, 7, 23, 1, 44, 4, 11, 33, 12, 27, 2, 38, 24, 28, 32, 14, 50};
	//vector<int> v = {16, 30, 9, 17, 40, 13, 42, 5, 25, 49, 7, 23};


	cout << "Coins " << endl;
	cout << "-----------------------------------" << endl;
	for (auto i : v)
		cout << i << endl;

	cout << "Coins " << "\t" << "Numbers" << endl;
	cout << "-----------------------------------" << endl;
	long unsigned ans = max_value(v, 245);
	cout << "------Result------------" << endl;
	cout << ans << endl;

	return 0;
}
