/*-------------------------------------------------------------------
 *
 *  sub-matrix search
 *
 *-------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
	
	bool fflag_ = true;
	bool rflag_ = false;

	public :
		bool search_sub_matrix(vector<vector<int>> matrix, int target) {

			if (matrix.empty())
				return false;

			int max_row_ = matrix.size() - 1;
			int max_col_ = matrix.at(0).size() - 1;
		
			int r = 0, c = 0;
			bool done = false;
			bool found = false;

			while (!done) {
			
				cout << matrix.at(r).at(c) << endl;

				if (target < matrix.at(r).at(c)) {

					if (fflag_) {
						if (r >= max_row_)
							done = true;
						else {
							r++;	// Down
							fflag_ = false;
							rflag_ = true; // trigger reverse
						}
					} else if (rflag_) {
						if (c <= 0)
							done = true;
						else
							c--;
					} else {
						assert(0);
					}

				} else if (target > matrix.at(r).at(c)) {

					if (fflag_) {
						if (c >= max_col_) {
							fflag_ = false;
							rflag_ = true;
						} else {
							c++;
						}

					} else if (rflag_) {
						if (r >= max_row_) {
							done = true;
						} else {
							r++;	// Down
							//fflag_ = true;
							//rflag_ = false;
						}
					} else {
						assert(0);
					}
				} else {
					found = true;
					done = true;
				}
			}

			if (found)
				return true;
			else
				return false;
		}
};

int main(void) {

	//vector<int> v1 = {1, 4, 7, 11 ,15};	
	//vector<int> v2 = {2, 5, 8, 12 ,19};	
	//vector<int> v3 = {3, 6, 9, 16 ,22};	
	//vector<int> v4 = {10, 13, 14, 17, 24};	
	//vector<int> v5 = {18, 21, 23, 26, 30};	

	vector<int> v1 = {1, 2, 3, 4, 5};	
	vector<int> v2 = {6, 7, 8, 9, 10};	
	vector<int> v3 = {11, 12, 13, 14, 15};	
	vector<int> v4 = {16, 17, 18, 19, 20};	
	vector<int> v5 = {21, 22, 23, 24 ,25};	

	//vector<int> v4 = {10, 13, 14, 17, 24};	
	//vector<int> v5 = {18, 21, 23, 26, 30};	

	vector<vector<int>> v;
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);
	v.push_back(v5);

	Solution *sol = new Solution();
	if (sol->search_sub_matrix(v, 8))
		cout << " true" << endl;
	else
		cout << " false" << endl;

	delete sol;

	return 0;
}
