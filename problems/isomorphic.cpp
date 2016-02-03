/*----------------------------------------------------------------
 *
 * isomorphic strings
 *
 * ---------------------------------------------------------------*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Isomorphic {

	unordered_map<char, char> map_;

	public:

	bool checkIsomorphic(string s1, string s2) {

		int i = 0;
		int p = 0;

		if (s1.length() != s2.length())
			return false;

		p = s1.length();

		while (i < p) {
			if (map_.find(s1.at(i)) == map_.end()) {
				map_[s1.at(i)] = s2.at(i);
			} else if (map_[s1.at(i)] != s2.at(i)) {
				return false;
			} 
			i++;
		}		
		return true;
	}

	void print_map(void) {
		
		for (auto i : map_)
			cout << i.first << endl;
	}
}; 

int main(void) {

	const string s1 = "abbcd";
	const string s2 = "xyyzk";

	Isomorphic *p = new Isomorphic();
	cout << "Isomorphic : " << p->checkIsomorphic(s1, s2) << endl;
	//p->print_map();	
	return 0;
}

