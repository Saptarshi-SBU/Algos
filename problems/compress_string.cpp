/*------------------------------------------------------------------------------
 *
 * Copyright(C) 2017 Saptarshi Sen
 *
 * Compress String
 *
 *  +) Algorithm :run length encoding
 *
 *  +) Use pointer for O(1) space complexity
 *
 *  +) For multi-digit frequency, store count as array of char digits
 *
 * Given an array of characters, compress it in-place.
 * Every element of the array should be a character (not int) of length 1.
 *
 * Complexity : O(n), Space O(1)
 *
 * https://leetcode.com/submissions/detail/133877636/
 *
 * ---------------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {

    public:

    // Desc : updates array in-place
    //
    // @param ch : character
    // @param placemarker
    // @param frequency
    void update(vector<char>& chars, char ch, int& placemarker, int frequency) {
        if (!frequency) {
            return;
        }
        chars[placemarker++] = ch;
        if (frequency > 1) {
            std::string count_s = std::to_string(frequency);
            for (auto& i : count_s) {
                chars[placemarker++] = i;
            }
        }
    }

    // Main compression routine
    int compress(vector<char>& chars) {
        char prev = '\0';
        int placemarker = 0, frequency = 0;
        for (int i = 0; i < chars.size(); i++) {
            if (prev == chars[i]) {
                frequency++;
            } else {
		// Compress the previous here
                update(chars, prev, placemarker, frequency);
                prev = chars[i];
                frequency = 1;
            }
        }
        // remaining character
        update(chars, prev, placemarker, frequency);
        chars.resize(placemarker);
        return placemarker;
    }

    void print(vector<char>& chars) {
	std::cout << "compressed " << std::endl;
        for (auto& i : chars) {
            std::cout << i;
        }
	std::cout << std::endl;
    }
};

int
main(void) {
  Solution sol;
  vector<char> vec = {'a','a','b','b','c','c','c'};
  sol.compress(vec);
  sol.print(vec);
  return 0;
}
