/*-----------------------------------------------------------------------------
 * Copyright (C) 2018, Saptarshi Sen
 *
 * Algorithm : Bottom-Up (using recursion)
 *
 * https://leetcode.com/submissions/detail/139500296/
 * ---------------------------------------------------------------------------*/

#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        return countAndSayUtil(n);
    }

    string countAndSayUtil(int n) {
        if (n == 0) {
            return std::string();
        }

        if (n == 1) {
            return std::string("1");
        }

        int count = 0;
        char prev = '\0';
        string sub, res;
        sub = countAndSay(n - 1);
        for (auto i : sub) {
            if (prev == i) {
                count++;
	    } else {
		if (prev != '\0') {
                    res.append(to_string(count) + string(1, prev));
		}
                count = 1; prev = i;
            }
        }

        if (prev != '\0') {
            res.append(to_string(count) + string(1, prev));
        }
        return res;
    }
};

int main(void) {
    Solution sol;
    std::cout << sol.countAndSay(2) << std::endl;
    std::cout << sol.countAndSay(3) << std::endl;
    std::cout << sol.countAndSay(4) << std::endl;
    std::cout << sol.countAndSay(5) << std::endl;
    return 0;
}
