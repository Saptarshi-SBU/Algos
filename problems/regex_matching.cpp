/*----------------------------------------------------------------------
 *
 * Implement regular expression matching with support for ‘.’ and ‘*’.
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 *
 * https://leetcode.com/submissions/detail/88343902/
 *
 * g++ -std=c++11 -DDEBUG regex_matching.cpp
 * --------------------------------------------------------------------*/

#include <iostream>
#include <cassert>

using namespace std;

// Backtracking
bool isMatch2(const char* s, const char* p) {

    assert(s || p);

#if DEBUG
    cout << " character : " << *s
         << " pattern : "  << *p
         << endl;
#endif

    // if p ends and s does not
    if (*p == '\0')
        return (*s == '\0');
    // if p has wild-card
    else if (*(p + 1) == '*')
        //return ((*p == '.') || (*p == *s)) &&
        return 
               ((*s != '\0') && ((*p == *s) || (*p == '.')) &&
            //reduce the current character in s
                 (isMatch2(s + 1, p + 2) ||
            //repeat reduce next character in s
                  isMatch2(s + 1, p))) ||
            //skip the current pattern
                isMatch2(s, p + 2);
    else
        return ((*p == *s) || (*p == '.')) &&
                (*s != '\0') &&
                isMatch2(s + 1, p + 1);
}

// This recursive solution exceeded time limit in 
// leetcode. The following is an optimized version
// where we skip matched characters and do not start
// a recursive tree at each level.
bool isMatch3(const char* s, const char* p) {

    assert(s || p);

#if DEBUG
    cout << " character : " << *s
         << " pattern : "  << *p
         << endl;
#endif

    // if p ends and s does not
    if (*p == '\0')
        return (*s == '\0');
    // if p has wild-card
    else if (*(p + 1) == '*') {
        while ((*s != '\0') && ((*p == *s) || (*p == '.'))) {
            //skip the current pattern and spawn a new Match
                if (isMatch3(s, p + 2)) return true;
            //reduce the current character in s
            s++;
        }    
        //spawn new match for next unconsumed in string
        return isMatch3(s, p + 2);
    }        
    else
        return ((*p == *s) || (*p == '.')) &&
                (*s != '\0') &&
                isMatch3(s + 1, p + 1);
}

#define TEST_STRING01  "abc"
#define TEST_PATTERN01 "a"
#define TEST_PATTERN02 "ab"
#define TEST_PATTERN03 "abc"
#define TEST_PATTERN04 "*"
#define TEST_PATTERN05 ".*"
#define TEST_PATTERN06 ".*."
#define TEST_PATTERN07 "ab.*d"

#define TEST_STRING02  "a"
#define TEST_PATTERN08 ".*..a*"

#define TEST_STRING04  "a"
#define TEST_PATTERN10 "ab*"

#define TEST_STRING05  "abcd"
#define TEST_PATTERN11 "d*"

#define TEST_STRING06 "aaaaaaaaaaaaab"
#define TEST_PATTERN12 "a*a*a*a*a*a*a*a*a*a*c"

int main(void) {
    bool ans;
    cout << "expected\t" << "result" << endl;
#if 1
    ans = isMatch3(TEST_STRING01, TEST_PATTERN01);
    cout << "0\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING01, TEST_PATTERN02);
    cout << "0\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING01, TEST_PATTERN03);
    cout << "1\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING01, TEST_PATTERN04);
    cout << "0\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING01, TEST_PATTERN05);
    cout << "1\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING01, TEST_PATTERN06);
    cout << "1\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING01, TEST_PATTERN07);
    cout << "0\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING02, TEST_PATTERN08);
    cout << "0\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING04, TEST_PATTERN10);
    cout << "1\t\t" << ans << endl;
#endif
    ans = isMatch3(TEST_STRING05, TEST_PATTERN11);
    cout << "0\t\t" << ans << endl;

    ans = isMatch3(TEST_STRING06, TEST_PATTERN12);
    cout << "0\t\t" << ans << endl;

    return 0;
}
