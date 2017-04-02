/*-------------------------------------------------------------------------
 * Copyright(C) : 2017, Saptarshi Sen
 *
 * Merge Two Sorted Arrays O(n)
 *
 * https://leetcode.com/submissions/detail/98769283/
 *
 *------------------------------------------------------------------------*/

#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {

public:

       void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        if (!n)
           return;

        assert (nums1.size() >= m);

        int nr = m + n;

        // Resize the vector
        // Note : for vectors nums1[i] and nums.at(i) hold different meaning
        // the former will hold if vector size is less than i, the latter not
        // also specifiying m > nums1.size(), indicate that the rest elements
        // will be initialized to zero.
        nums1.resize(nr);

        // Set the iterators
        auto iter1 = nums1.rbegin() + n;
        auto iter2 = nums2.rbegin();

        // Position Counter
        int c = nr - 1;

        for (; c >= 0 ; c--) {
            if ((iter1 == nums1.rend()) || (iter2 == nums2.rend()))
               break;

            if (*iter1 <= *iter2) {
               nums1.at(c) = *iter2;    
               iter2++;
            } else {
               nums1.at(c) = *iter1;
               iter1++;
            }
        }

        for (;iter2 != nums2.rend(); iter2++, c--)
           nums1.at(c) = *iter2;
    }
};

int main(void) {
   int m = 2;
   vector<int> nums1 = {2, 3} ;
   int n = 1;
   vector<int> nums2 = {1};

   Solution sol;
   sol.merge(nums1, m, nums2, n);
   for (auto&i : nums1)
       cout << i << " ";
   cout << endl;
   return 0;
}
