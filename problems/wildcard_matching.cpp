/*-------------------------------------------------------------------------
 * Implement wildcard pattern matching with support for '?' and '*'.
 *
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 *
 * https://leetcode.com/submissions/detail/88371952/
 * ------------------------------------------------------------------------*/

#include <iostream>

using namespace std;

//Backtracking using recursion
bool isMatch(const char* s, const char* p) {

   if (s == NULL || p == NULL)
      return false;

   if (*p == '\0')
      return (*s == '\0');
   
   if (((*p == *s) || (*p == '?')) && (*s != '\0'))
       return isMatch(s + 1, p + 1);
 
   while (*p == '*') {
      if (*(p + 1) == '*') {
        p++;
        continue;
      }  
      if ((*(p + 1) == '\0') || (isMatch(s, p + 1)))
         return true;
      else if (*s != '\0')
         s++;
      else
         break; 
   }

   return false;   
}

//Backtracking based on two pointers. The previous recursive 
//solution hit time exceeded in leetcode submissions
bool isMatch2(const char* s, const char* p) {

   if (s == NULL || p == NULL)
      return false;

   int anchor_pat = -1;
   int anchor_str = -1;

   int i,j;
   i = j = 0;

   while (s[i] != '\0') {
#if DEBUG
      cout << "p : " << p[j] << "\t"
           << "s : " << s[i] << endl; 
#endif      
      if ((p[j] == '?') || (p[j] == s[i])) {
         j++;
         i++; 
      } else if (p[j] == '*') {
      //If pattern[m] == ‘*’, if ‘*’ matches with current character in
      //input string we will move to next character in the string else
      //we ignore ‘*’ and move to next. Note anchor is used here to
      //store the points from where we can backtrack
         anchor_pat = j;
         anchor_str = i;
         j++;
      } else if (anchor_pat >= 0) {
         j = anchor_pat;
         i = anchor_str + 1;  
         anchor_pat = anchor_str = -1;
      } else
         return false;   
   }    

   while (p[j] != '\0' && p[j] == '*')
       j++;

   return p[j] == '\0';
}

#define TEST_STRING01  "aa"
#define TEST_STRING02  "aaa"
#define TEST_STRING03  "ab"
#define TEST_STRING04  "aab"
#define TEST_STRING05  "bb"
#define TEST_STRING06  "abcdabd"
#define TEST_STRING07  "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba"
#define TEST_STRING08  "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb"

#define TEST_PATTERN01 "a"
#define TEST_PATTERN02 "aa"
#define TEST_PATTERN03 "*"
#define TEST_PATTERN04 "a*"
#define TEST_PATTERN05 "?*"
#define TEST_PATTERN06 "c*a*b"
#define TEST_PATTERN07 "*b"
#define TEST_PATTERN08 "*d"
#define TEST_PATTERN09 "*ed"
#define TEST_PATTERN10 "a*******b"
#define TEST_PATTERN11 "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb"

int main(void) {

    bool ans;

    cout << "expected\t" << "result" << endl;

    ans = isMatch2(TEST_STRING01, TEST_PATTERN01);
    cout << "0\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING01, TEST_PATTERN02);
    cout << "1\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING02, TEST_PATTERN03);
    cout << "1\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING03, TEST_PATTERN04);
    cout << "1\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING04, TEST_PATTERN06);
    cout << "0\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING05, TEST_PATTERN07);
    cout << "1\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING06, TEST_PATTERN08);
    cout << "1\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING06, TEST_PATTERN09);
    cout << "0\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING07, TEST_PATTERN10);
    cout << "0\t\t" << ans << endl;

    ans = isMatch2(TEST_STRING08, TEST_PATTERN11);
    cout << "0\t\t" << ans << endl;

    return 0;
}    
