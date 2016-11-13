/*------------------------------------------------------
 *  Roman Numeral and Integer Conversion Routines
 *  
 *  g++ -o main -std=c++11 numeral_conversion.cpp
 *-----------------------------------------------------*/

#include <map>
#include <stack>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unistd.h>

using namespace std;

#define DEBUG 0

std::map<char, int> rtable = {
         {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
         {'C', 100}, {'D', 500}, {'M', 1000}};

std::map<string, int> rtable2 = {
         {"I", 1}, {"IV", 4}, {"V", 5}, {"IX", 9}, 
         {"X", 10}, {"XL", 40}, {"L", 50}, {"XC", 90},
         {"C", 100}, {"CD", 400}, {"D", 500}, {"CM", 900}, 
         {"M", 1000}};

std::map<int, string> itable = {
         {1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, 
         {10, "X"}, {40, "XL"}, {50, "L"}, {90, "XC"},
         {100, "C"}, {400, "CD"}, {500, "D"}, {900, "CM"}, 
         {1000, "M"}};

class Solution {

public:
    int romanToInt(string s) {
        if (0 == s.length())
            throw std::invalid_argument("Empty String");
        // Convert  
        int sum = 0; 
        int prev = 0;
        for (auto r = s.rbegin(); r != s.rend(); r++) {
#if DEBUG
            cout << "RI " << *r << endl;
#endif
            if (rtable.find(*r) == rtable.end())
                throw std::invalid_argument("Invalid Character");
            else {
                auto curr = rtable[*r];
                if (!prev)
                    sum = curr;
                else {
                    if (curr < prev)
                        sum-=curr;
                    else
                        sum+=curr;
                }
                prev = curr;
            }
#if DEBUG            
            //cout << sum << endl;
#endif
        }
        return sum;
    }

    int romanToInt2(string s) {
        int sum = 0;
        int n = s.length();

        if (!n)
            throw std::invalid_argument("Empty String");

        int next = 0;
        while(next < n) {
            auto s1 = s.substr(next, 1);
            auto s2 = s.substr(next, 2);

            if (rtable2.find(s2) != rtable2.end()) {
                sum+=rtable2[s2];
                next+=2;
            } else if (rtable2.find(s1) != rtable2.end()) {
                sum+=rtable2[s1];
                next+=1;
            } else    
                throw std::invalid_argument("Invalid Character");
        }
        return sum;
    }

     string intToRoman(int num) {
         string ans;
         if (num <= 0)
             throw std::invalid_argument("Invalid integer");
                
         stack<int> s;
         for (auto i : itable)
             s.push(i.first); 
         
         while (num > 0) {
             int base = s.top();
             s.pop();
             if (base > num)
                continue;
             int n = num/base; 
             for (;n;n--)
                 ans.append(itable[base]);  
             num = num % base;
         }
         return ans;
     }
};

int main(int argc, char **argv) {
     char c;

     if (argc < 3) {
         cout << "Usage :  -r <roman>/-i <integer" << endl;
         return -1;
     }    

     Solution *sol = new Solution();
     while ((c = getopt (argc, argv, "i:r:")) != -1) {
         switch (c) {
             case 'r' :
             cout << sol->romanToInt2(string(optarg)) << endl;
             break;
             case 'i':
             cout << sol->intToRoman(atoi(optarg)) << endl;
             break;
        }
     }     

     return 0;
}
