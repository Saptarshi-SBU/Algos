/*------------------------------------------------------------------------------------
 *
 *  Binary addition of two  bit streams
 *  
 *  Recursive solution
 *  Date : 03/31/2016
 * -----------------------------------------------------------------------------------*/

#include <iostream>
#include <string>

using namespace std;

class Solution {

    string addBinaryUtil(string a, string b, int carry) {

        if (a.empty() && b.empty())
            return  carry ? "1" : "";

        else if (a.empty())
            return carry ? addBinaryUtil(b, "1", 0) : b;

        else if (b.empty())
            return carry ? addBinaryUtil(a, "1", 0) : a;

        else {

            int p = a.length();

            int q = b.length();

	    int sum  = a.at(p - 1) - '0' + b.at(q - 1) - '0' + carry;	

	    return addBinaryUtil(a.substr(0, p - 1), b.substr(0, q - 1), sum/2) + to_string(sum % 2);		    
	
        }    
    }
public:

    string addBinary(string a, string b) {
	return addBinaryUtil(a, b, 0);
    }		

};

int main(void) {
	Solution *sl = new Solution();
	string s1 = "00110";
	string s2 = "1111";
	cout << s1 << "+" << s2 << "=" << sl->addBinary(s1, s2);
	return 0;
}
