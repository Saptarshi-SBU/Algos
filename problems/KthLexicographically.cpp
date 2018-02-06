/*----------------------------------------------------------------------------------------------------------------------------------------------------
 * Copyright (C) 2018, Saptarshi Sen
 *
 * Algorithm : denary tree
 *
 * https://leetcode.com/submissions/detail/139668189/
 *
 * More Reference :
 * https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/discuss/92242/ConciseEasy-to-understand-Java-5ms-solution-with-Explaination
 *
 * ---------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <set>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
	// O(n) space, O(nlogn) + O(n) time
        int findKthNumberWithTree(int n, int k) {
            set<string> s;
            for (int i = 1;i <= n; i++) {
                s.insert(to_string(i));
            }

            std::string value;
            auto iter = s.begin();
            for (int i = 0; (iter != s.end()) && i < k; i++, iter++) {
                //cout << *iter << endl;
                value = *iter;
            }
            return atoi(value.c_str());
        }

        // O(1) space, O(k) time
	int findKthNumber(int n, int k) {
           int nr_nodes = 0;
           int cur_node = 1, next_node;

	   while (k > 1) {
               next_node = cur_node + 1;
	       nr_nodes = distance(cur_node, next_node, n);
	       std::cout << " cur  :" << cur_node
		         << " next :" << next_node
			 << " nr_nodes :" << nr_nodes
			 << " k :" << k
			 << " n :" << n << std::endl;
	       // go to next sub-tree, i.e. sibling in the same level
	       if (nr_nodes < k) {
	           cur_node += 1;
		   k -= nr_nodes;
	       // remain in this sub-tree since it can accomodate
	       // more elements than k in the sub-tree i.e. down to children
               } else if (nr_nodes >= k) {
                   cur_node *= 10;
		   k -= 1;
	       }
	   }
	   return cur_node;
        }

	long distance(long p, long q, long n) {
            long d = 0;
            while (p <= n) {
		// count number of elements between p and q (all inclusive)
		//  Not : n + 1 (target) vs q (next node)
                d += std::min(n + 1, q) - p;
                p *= 10;
		q *= 10;
	    }
	    return d;
	}
};

int main(void) {
    Solution sol;
    std::cout << sol.findKthNumber(130, 4) << std::endl;
    std::cout << sol.findKthNumber(100, 90) << std::endl;
    return 0;
}
