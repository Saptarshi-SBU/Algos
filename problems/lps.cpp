/*-----------------------------------------------------------------------------------------
 *
 *  Longest Palindromic substring : Dynamic Programming (O(n2)
 *
 *------------------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

using namespace std;

class LPS {
    
    string str_;
    
    public :
    
        LPS(string str) : str_(str) {}
       ~LPS() {}
       
        int expand_around_centre(string s, int l, int r) {
            
            int c = 0;
            
            while ((l >=0) && (r < s.length())) {
                    if (s.at(l) == s.at(r)) {
                            c++;
                            l--;
                            r++;
                    } else {
                            break;
                    }
            }
            return c;
        }
    
        int lps(void) {
            
            int i = 0;
            int longest = 0;
            
            for (i = 0; i < str_.length(); i++) {
                int p1 = expand_around_centre(str_, i, i) - 1;
                int p2 = expand_around_centre(str_, i, i + 1);
                int p = max(2*p1 + 1, 2 *p2);
                if (longest < p)
                    longest = p;
            }
            
            return longest;
        }

};


int main(void) {
    string s = "AAAAABAAAAAC";
    LPS *lp = new LPS(s);
    cout << "Longest Palimdromic Substring " << lp->lps() << endl;
}