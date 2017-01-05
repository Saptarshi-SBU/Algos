/*-----------------------------------------------------------------------
 * palindrome integer
 *
 * Constraint minimum space
 *
 * ---------------------------------------------------------------------*/
#include <iostream>

using namespace std;

// First, compare the first and last digit. If they are not the same, 
// it must not be a palindrome. If they are the same, chop off one 
// digit from both ends and continue until you have no digits left, 
// which you conclude that it must be a palindrome.

bool palindrome(int n) {

    if (n < 0)
        return false;

    int div = 1;
    while (n/div >=10)
       div*=10;

    while (n != 0) {
       int l = n / div;
       int r = n % 10;
       if (l != r)
          return false; 
       n = (n % div) / 10;
       div /=100;
    }    

    return true;
}   

// recursion based
//
bool ispalindrome(int p, int& q) {
    if (p < 0)
        return false;
    if (p == 0)
        return true;
    if (ispalindrome(p/10, q) && (p%10 == q%10)) {
        q /= 10;
        return true;
    } else 
        return false; 
}

int main(void) {
    int val = 1001;
    cout << palindrome(val) << endl;
    cout << ispalindrome(val, val) << endl;
    return 0;
}    
