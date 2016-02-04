/*------------------------------------------------------------
 *
 * first non repeating char
 *
 *-----------------------------------------------------------*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <climits>

using namespace std;

class Map {

	unordered_map<char, pair<int, int>*> map_;
	
	public :

		void push(string s, int i) {

			if (map_.find(s.at(i)) == map_.end()) {
				map_[s.at(i)] = new pair<int, int>(1, i);
				return;
			} else {
				pair<int, int> *p = map_[s.at(i)];
				p->first+=1;
				return;
			}
		}

		void print_map(void) {
	
			for (auto i : map_)
				cout << i.first;
			cout << endl;			
		}

		int first_non_repeating_char(void) {
		
			int  min = INT_MAX;

			for (auto i : map_)
				if ((1 == i.second->first) && (i.second->second < min))
					min = i.second->second; 
				
			return min;
		}
};

int main(void) {

	Map m;
 
	string base = "xyzabcdfgrghujghbfghjaxy";

	int i = 0;
	int k = 0;
	int p = base.length();

	cout << base << endl;
	for (i = 0; i < p; i++) {
		m.push(base, i);
		//m.print_map();
		k = m.first_non_repeating_char();
		if (k <= i)	
			cout << base.at(k) << endl;
	}

	return 0; 
}


