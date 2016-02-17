/*---------------------------------------------------------------------------------------
 *
 * string sig-zag print
 *
 * --------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>

using namespace std;

class Solution {

public:

    string convert(string s, int numRows) {

        int max, dst, len;
	string str;

        max = dst = 0;
        len = s.length();

        for(int row = 1; row <= numRows; row++) {

            for (int rounds = 1, k = row; k <= len; rounds++) {

                max = (rounds * numRows) - (rounds - 1);
                dst = k % max;
                if (dst){
                	str.append(1, s.at(k-1));
			k = k +  2 * (max - dst);
		}
             }
        }
    }
};

int main(void) {

	string s = "ABC";
	Solution *sol = new Solution;
	cout << sol->convert(s, 5) << endl;
	return 0;	
}
