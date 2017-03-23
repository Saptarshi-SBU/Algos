/*----------------------------------------------------------------------------
 *
 * Copyright (C) 2017 Saptarshi Sen
 *
 * Reverse an integer
 *
 * https://leetcode.com/submissions/detail/97723928/
 *
 * --------------------------------------------------------------------------*/

#include <iostream>
#include <limits>
#include <cassert>
#include <stdexcept>

using namespace std;

class Solution {

public:
    inline int SafeMul(const int p, const int q) {
       // Note : check for division by 0
       assert(q);    
       // Fix : check for equals as well
       if (std::numeric_limits<int>::max()/q >= p) 
          return p*q;
       else  
          throw std::overflow_error("Multiplication Overflow");
    }

    inline int SafeAdd(const int p, const int q) {
       if (std::numeric_limits<int>::max() - q >= p) 
          return p + q;
       else  
          throw std::overflow_error("Addition Overflow");
    }    

    int reverse(int x) {
        int p = 0;
        int q = abs(x);
        do {
           try {
              int r = q % 10;
              p = SafeAdd(SafeMul(p, 10), r);
              q = (q - r)/10;
           } catch (std::overflow_error& e) {
              return 0;    
           }   
        } while (q);    
        return (x < 0) ? -p : p;
    }
};

int main(void) {
   Solution sol;
   cout << sol.reverse(-49) << endl;
   return 0;
}
