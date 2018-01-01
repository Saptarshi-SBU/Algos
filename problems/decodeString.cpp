/*------------------------------------------------------------------------------
 *
 * Copyright(C) 2017 Saptarshi Sen
 *
 * Decode String (Expand String)
 *
 * Given an encoded string, return it's decoded string.
 *
 * The encoding rule is: k[encoded_string], where the encoded_string inside the
 * square brackets is being repeated exactly k times. Note that k is guaranteed
 * to be a positive integer.
 *
 *  +) Algorithm : Deterministic Finite Automata
 *
 * Complexity : O(n)
 *
 * https://leetcode.com/submissions/detail/134107323/
 *
 * ---------------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {

    public:

    // Desc : Decode core routine (DFA based)
    // @param encoded string
    // @param pos
    // returns : expanded string
    string decode(string& encoded, int& pos) {
        int count = 0;
        string decoded;

        if (encoded.empty()) {
            return string();
        }

        while (isdigit(encoded.at(pos))) {
            count = count * 10 + (encoded.at(pos) - '0');
            pos++;
        }

        while (pos < encoded.length()) {
            if (encoded.at(pos) == '[') {
                pos++;
            } else if (encoded.at(pos) == ']') {
                pos++;
                break;
            } else if (isdigit(encoded.at(pos))) {
                decoded.append(decode(encoded, pos));
            } else {
                decoded.append(1, encoded.at(pos));
                pos++;
            }
        }

        string expanded;
        // Fixed : do not self-append
        for (int i = 0; i < count; i++) {
            expanded.append(decoded);
        }

        if (count) {
            decoded = expanded;
        }

        return decoded;
    }

    // Main decode routine
    string decodeString(string s) {
        int pos = 0;
        string decoded;
        while (pos < s.length()) {
            decoded.append(decode(s, pos));
        }
        return decoded;
    }

    void print(string decoded) {
	std::cout << decoded << std::endl;
    }
};

int
main(void) {
  Solution sol;
  string encoded = "2[abc]3[a]";
  string decoded = sol.decodeString(encoded);
  std::cout << "compressed " << std::endl;
  sol.print(encoded);
  std::cout << "decompressed " << std::endl;
  sol.print(decoded);
  return 0;
}
