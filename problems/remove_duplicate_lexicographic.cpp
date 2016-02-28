/*----------------------------------------------------------------------------
 *
 * lexico-graphic based remove duplicates
 *
 * --------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <climits>
#include <cassert>

using namespace std;

class Solution {

	private :

		int lookup_last_minimum(void) {
			int min = INT_MAX;
			if (map_.empty())
			   return -1;
			for (auto i : map_)
			   if (min > i.second)
			     	min = i.second;
			return min;		
		}

		int lookup_last_minimum2(void) {
			int last = INT_MAX;
			for (int i = 0; i < 26; i++)
			   if ((dict[i] >= 0) && (dict[i] < last))
			     	last = dict[i];
			return last;
		}

	public  :

		map<char, int> map_;	
		int dict[26];

		string removeDup_lexicographic_smallest2(string str) {

			int count = 0;
			int chars = 0;

			string result;

			if (str.empty())
			   return str;

			for (int i = 0; i < 26; i++)
			   dict[i] = -1;	

			for (auto i : str) {
			   if (dict[i - 'a'] < 0)
				chars++;	
			   dict[i - 'a'] = count++;
			}
	
			int  i = 0;
			int  p = 0; // start
			int  q = 0; // minimum last

			while (chars) {

				char schar = 0x7F;	// initialize max value
				q = lookup_last_minimum2();
				assert (q >= 0);

				for (i = p; i <= q; i++) {
					if  ((str.at(i) < schar) && (dict[str.at(i) - 'a'] >= 0)) {
						schar = str.at(i);
						p = i;
					}
				}

			    	p = p + 1;
				dict[schar - 'a'] = -1;
				result.append(1, schar);
				chars--;
			}

			return result;	
		}

		string removeDup_lexicographic_smallest(string str) {

			int count = 0;
			string result;

			if (str.empty())
				return str;

			for (auto i : str)
			   map_[i] = count++;

			int  i = 0;
			int  p = 0; // start
			int  q = 0; // minimum last

			while (!map_.empty()) {

				char schar = 0x7F;	// initialize max value
				q = lookup_last_minimum();
				assert (q >= 0);

				for (i = p; i <= q; i++) {
					if  ((str.at(i) < schar) && (map_.find(str.at(i)) != map_.end())) {
						schar = str.at(i);
						p = i;
					}
				}

			    	p = p + 1;
				map_.erase(schar);
				result.append(1, schar);
			}

			return result;	
		}

};

int main(void) {

	Solution *sol = new Solution();
	cout << sol->removeDup_lexicographic_smallest2("eeabccabd") << endl;
	cout << sol->removeDup_lexicographic_smallest2("cbacdcbc") << endl;
	cout << sol->removeDup_lexicographic_smallest2("bcabc") << endl;
	cout << sol->removeDup_lexicographic_smallest2("baab") << endl;
	return 0;
}
