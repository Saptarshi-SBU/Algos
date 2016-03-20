/*-----------------------------------------------------------------------------------
 *
 * Minimum Edit Distance
 *
 * Date : 03/27/2016
 *
 * Test Case : "sea" "eat" : should give 2
 * ----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MIN(a, b, c) min(min(a, b), c)

class Solution {

	public :
		
		int compute_edit_distance(string s1, string s2) {

			if (s1.empty() && s2.empty())
				return 0;
		
			s1.insert(0, 1, '$');
			s2.insert(0, 1, '$');
				
			int p, q;
			vector<vector<int>> ed_ (s1.length() + 1, vector<int> (s2.length() + 1, 0));

			ed_[0][0] = 0;
			for (p = 1; p < s1.size(); p++) 
				ed_[p][0] = ed_[p - 1][0] + 1;
				
			for (q = 1; q < s2.size(); q++) 
				ed_[0][q] = ed_[0][q - 1] + 1;
				
			for (p = 1; p < s1.size(); p++) {

				for (q = 1; q < s2.size(); q++) {

					if (s1.at(p) == s2.at(q))
						ed_[p][q] = ed_[p - 1][q - 1];
					else
						ed_[p][q] = MIN(ed_[p - 1][q - 1], ed_[p][q - 1], ed_[p - 1][q]) + 1;
					
					cout << ed_[p][q] << " ";
				}
				
				cout << endl;
			}

			return (ed_[p - 1][q - 1]);
		}
};

int main(void) {
	string str1, str2;
	Solution *sol = new Solution;
	cout << "Enter First String ";
	cin >> str1;	
	cout << "Enter Second String ";
	cin >> str2;	
	cout << "Edit distance " <<  ": " << sol->compute_edit_distance(str1, str2) << endl;
	return 0;
}

