/*------------------------------------------------------------------------------
 *
 * Copyright(C) : 2017 Saptarshi Sen
 *
 * Problem: Given an array nums, we call (i, j) an important reverse pair if i <
 * j and nums[i] > 2*nums[j]. You need to return the number of important reverse
 * pairs in the given array.
 *
 * Algorithm I: Order-Statistic BST O(nlogn). (for counting number of elements >
 * x in the tree). In this program, we use STL distance. But that is linear time
 * becuase set/multiset do not have random access iterators.
 *
 * Notes : http://stackoverflow.com/questions/15321013/c-set-counting-elements-less-than-a-value
 * As for relationship with random access iterators, there isn't any: map iterators
 * are bidirectional. Distance is linear.
 *
 * Algorithm II: Merge-Sort. We count in the merge phase. The count algorithm is
 * linear-time
 *
 * https://leetcode.com/submissions/detail/97371438/
 * ----------------------------------------------------------------------------*/

#include <set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
   public:

    int reversePairs01(vector<int>& nums) {
       int count = 0;
       multiset<long long int, std::less<long long int>> bst;

       for (auto iter = nums.begin(); iter != nums.end(); iter++) {
          long long int p = *iter;
          // Note : sets with no random access iterators, distance is O(n)
          count+=std::distance((bst.upper_bound(2 * p)), bst.end());
          // bst for logn bound search
          bst.insert(p);
       }
       return count;
    }

    int reversePairs02(vector<int>& nums) {
       return merge_sort(nums, 0, nums.size() - 1);
    }

    int merge(vector<int>&nums, int p, int q) {

        int count = 0;
        //Fix : Note Operator precedence '+' > '>>'
        //      Divide by 2 is NOT >> 2!
        int m = p + ((q - p) >> 1);

        // LP & RP. We scan in reverse
        int i = m; // LP
        int j = q; // RP
        int last = -1;
#if DEBUG
        cout << "DBG : " << p << ":" << q << endl;
#endif
        // Linear time count, core of this algorithm
        while (j > m) {
            // store LP pointer
           if (2L * nums.at(j) < nums.at(i)) {
              last = i;
              cout << "Pair :" << nums.at(i) << ":" << nums.at(j) << endl;
              i--;
           } else {
              // If any valid anchor in LP
              if (last >= 0) {
                 count+=(m - last + 1);
              }
              j--;
           }

           // LP: We exhaust all LP elements
           // Fix i NOT less than 0
           if (i < p) {
              size_t length = m - p + 1;
              count+=(j - m)*length;
              break;
           }
        }

        // LP min satisfies constraint for some q (q - m)
        // TBD: We can make it linear-time using actual copy-merge
        // Fix : sort last iterator is NOT '+ q' but 'q + 1'
        std::sort(nums.begin() + p, nums.begin() + q + 1);
#if DEBUG
        for (auto iter = nums.begin() + p; iter <= (nums.begin() + q); iter++)
            cout << *iter << " ";
        cout << endl;
#endif
        return count;
    }

    int merge_sort(vector<int>&nums, int p, int q) {
        if (p >= q) return 0;
        int m = p + ((q - p) >> 1);
        return merge_sort(nums, p, m) +
               merge_sort(nums, m + 1, q) +
               merge(nums, p, q);
    }
};

int main(void) {
    //vector<int> nums = {1, 2, -1};
   //vector<int> nums = {1, 2, 4, 6};
   //vector<int> nums = {6, 4, 2, 1};
   //vector<int> nums = {1,3,1, 6};
   //vector<int> nums = {2147483647,2147483647,2147483647,2147483647,2147483647,2147483647};
   vector<int> nums = {1,3,2,3,1};
   Solution sol;
   cout << "reversePairs " << sol.reversePairs01(nums) << endl;
   cout << "reversePairs " << sol.reversePairs02(nums) << endl;
   return 0;
}
