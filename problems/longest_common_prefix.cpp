/*---------------------------------------------------------------
  Longest common prefix amongst array of strings O(mn)

  https://leetcode.com/submissions/detail/129731209/

----------------------------------------------------------------*/
#include <vector>
#include <string>
#include <iostream>

class Solution {
public:
    typedef enum {
        START = 0,
        SCAN = 1,
    } state_t;

    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        int i;
        std::string result;

        if (strs.empty()) {
            return result;
        }

        i = 0;
        do {
            char c;
            state_t state;
            for (int j = 0, state = START; j < strs.size(); j++, state = SCAN) {

                if (i >= strs[j].length()) {
                    goto out;
                }

                if (state == SCAN && c != strs[j][i]) {
                    goto out;
                }

                if (state == START) {
                    c = strs[j][i];
                }
            }

            i++;
            result.append(1, c);

        } while (true);
out:
        return result;
    }
};

int main(void) {
    Solution sol;
    std::vector<std::string> strs{ "vodoo", "vod" };
    std::cout << sol.longestCommonPrefix(strs) << std::endl;
    return 0;
};
