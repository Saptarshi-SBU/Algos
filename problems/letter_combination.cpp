/*
 * Copyright (C) 2017 Saptarshi Sen
 *
 * Letter combination of a phone number
 *
 * Approach : Recursion
 *
 * Complexity : Exponential ~(3^n)
 *
 * https://leetcode.com/submissions/detail/130920226/
 */

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:

    const std::map<char, std::string> bmap = {
       { '2', "abc" },
       { '3', "def" },
       { '4', "ghi" },
       { '5', "jkl" },
       { '6', "mno" },
       { '7', "pqrs" },
       { '8', "tuv" },
       { '9', "wxyz" },
    };


    // Wrapper for sanity checks and main function invocation
    std::vector<std::string> letterCombinations(std::string digits) {
       std::vector<std::string> result;

       if (digits.empty()) {
           goto bad_input;
       }

       for (auto &s : digits) {
          if (bmap.find(s) == bmap.end()) {
             goto bad_input;
          }
       }

       generateCombinations(digits, 0, result);

       return result;

    bad_input:
       return std::vector<std::string>();
    }

    // Main function
    void generateCombinations(std::string digits, int pos,
       std::vector<std::string>& parent) {
       if (pos >= digits.length()) {
	   return;
       }
       //bmap defined as const, [i] returns non-const, so used at(i)
       auto kv = bmap.find(digits.at(pos));
       // double implicit conversion not allowed, so explicit conversion
       std::string items(kv->second);
       for (auto item = items.begin();item != items.end();item++) {
          std::vector<std::string> child;
	  generateCombinations(digits, pos + 1, child);
          for (auto &str : child) {
             str.insert(0, 1, *item);
          }
	  if (child.empty()) {
	     child.push_back(std::string(1, *item));
	  }
	  parent.insert(parent.end(), child.begin(), child.end());
       }
    }
};

int main(void) {
   Solution sol;
   std::vector<std::string> ans;
   ans = sol.letterCombinations(std::string("23"));
   for (auto &i : ans) {
      std::cout << i << std::endl;
   }
   std::cout << "total count : " <<ans.size() << std::endl;
   return 0;
}
