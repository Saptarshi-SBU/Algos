/*-------------------------------------------------------------------------------
 * Copyright (C) 2017 Saptarshi Sen
 *
 * Given two strings s1 and s2, write a function to return true if s2 contains
 * the permutation of s1. In other words, one of the first string's permutations
 * is the substring of the second string.
 *
 * Algorithm : BST based O(NlogN)
 *
 * https://leetcode.com/submissions/detail/101566714/
 * -----------------------------------------------------------------------------*/
#include <string>
#include <set>
#include <iostream>

using namespace std;

class Solution {

public:

    bool checkInclusion(string s1, string s2) {
        if (s1.empty() || s2.empty() || (s2.length() < s1.length())) {
            return false;
        }

        multiset<char> bst1, bst2;

        for (auto i : s1) {
            bst1.insert(i);
        }

        for (auto i = 0; i < s1.length(); i++) {
            bst2.insert(s2.at(i));
        }

        int n = s2.length() - s1.length();

        for (auto i = 0; i <= n; i++) {
            bool match = true;
            for (auto i : s1) {
                // Note use of the BST count method
                if (bst1.count(i) != bst2.count(i)) {
                    match = false;
                    break;
                }
            }

            if (match) {
                return true;
            }

            auto iter = bst2.find(s2.at(i));
            // Passing iter to erase will only erase the respective element
            // and not the range
            bst2.erase(iter);
            if (i < n) {
               bst2.insert(s2.at(i + s1.length()));
            }
        }
        return false;
    }
};

int main(void) {
    string s1 = "hello";
    string s2 = "ooleh";
    Solution sol;
    cout << (sol.checkInclusion(s1, s2) ? "true" : "false") << endl;
    return 0;
}
