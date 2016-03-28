/*----------------------------------------------------------------
 *
 * isomorphic strings
 *
 * ---------------------------------------------------------------*/

#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

class Solution {

public:

    bool isIsomorphic(string s, string t) {
	 if (s.empty() && t.empty())
            return true;

        if (s.empty() || t.empty())
            return false;

        if (s.length() != t.length())
            return false;

        unordered_map<char, int> smap;
        unordered_map<char, int> tmap;

        string::iterator it1, it2; 
        for (it1 = s.begin(), it2 = t.begin(); it1 != s.end(); it1++, it2++) {
            if ((smap.find(*it1) == smap.end()) && (tmap.find(*it2) == tmap.end())) {
                 smap[*it1] = *it2;
                 tmap[*it2] = *it1;
            } else if ((smap.find(*it1) != smap.end()) && (tmap.find(*it2) != tmap.end())) {
                 if ((*it1 != tmap[*it2]) || (*it2 != smap[*it1]))
                    return false;
            } else
                 return false;    
        }
        return true;
    }
};

int main(void) {

	const string s1 = "abbcd";
	const string s2 = "xyyzk";

	//const string s1 = "abecd";
	//const string s2 = "xyyzk";

	Solution *sol = new Solution();
	cout << "Isomorphic : " << sol->isIsomorphic(s1, s2) << endl;
	
	delete sol;
	return 0;
}

