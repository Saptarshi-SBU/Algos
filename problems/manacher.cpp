/*-----------------------------------------------------------

  Manacher's Algorithm
  
  Note : The pre-processing of string is required for making 
         it work for even pairs as well.

--------------------------------------------------------------*/

#include <iostream>

using namespace std;

class Manacher {
    
    string str_;
    
    int *parray_;
    
    public :
        
        Manacher(string str) : str_(str) {}
       ~Manacher() {}
    
        string get_string() {
            
            return str_;
        }
    
        void build_parray(string str) {
                   
            int c = 0;     
            int r = 0; 
            int i = 0;
            int i_mirror = 0; 
            
            parray_ = new int[str.length()];
            
            for (i = 1, c = 0, r = 0; i < str.length() - 1; i++) {
   
                i_mirror = c - (c - i);
                
                if (i < r) 
                   parray_[i] = min(parray_[i_mirror], r - i);   
                else
                   parray_[i] = 0;
            
                
                while (str.at(i - parray_[i] - 1) == str.at(i + parray_[i] + 1)) {
                    parray_[i]++;
                    if (((i - parray_[i] - 1) < 0) || ((i + parray_[i] + 1) >= str.length()))
                         break;
                }    
                
                if (1 + parray_[i] > r) {
                        r = i + parray_[i];
                        c = i;
                }
                
                //cout << i << "  " << parray_[i] << "  " << str.at(i) << endl;
            }
        }   
        
        string preprocess_string(void) {
            int i = 0;
            string str;
            int p = str_.length();

            str.append(1, '#');
            for (i = 0; i < p; i++) {
                str.append(1, str_.at(i));
                str.append(1, '#');
            }
          
            return str;
        }
        
        string longest_palimdromic_substring(string str) {
            
            int i = 0;
            int maxl = 0;
            int maxc = 0;
            
            for ( i = 0; i < str.length(); i++) {
                if (maxl < parray_[i]) {
                    maxl = parray_[i];
                    maxc = i;
                }
            } 
            
            cout << "Max Lenth " << maxl << endl;
            return str_.substr((maxc - maxl)/2, maxl);
        }
        
      
};


int main() {
    #if 1
    string str = "AAABCCBAAA";
	Manacher *m = new Manacher(str);
	string s = m->preprocess_string();
	cout << s<< endl;
	m->build_parray(s);
	cout << m->longest_palimdromic_substring(s);
	#else
	string str = "AAABCBAAA";
	Manacher *m = new Manacher(str);
	m->build_parray(m->get_string());
	cout << m->longest_palimdromic_substring(m->get_string()) << endl;
	#endif
	return 0;
}
