/*----------------------------------------------------------------------------
 * Copyright (C), 2017 Saptarshi Sen
 *
 * Given an integer array nums, return the number of range sums that lie in
 * [lower, upper] inclusive.
 * Range sum S(i, j) is defined as the sum of the elements in nums between
 * indices i and j (i ≤ j), inclusive.
 *
 * Algorithm : O (nlogn) based on merge sort technique applied on prefix-sum
 * array.
 *
 * https://leetcode.com/submissions/detail/100970246/
 * --------------------------------------------------------------------------*/
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
  public:
    int rmin;  // store problem's minimum limit
    int rmax;  // store problem's maximum limit
    vector<int> rvec;

    void print_range(vector<long int>& sum, int p, int q) const {
       cout << "nums range (" << p << "," << q << ")" << endl;
       for (int i = p; i < q; i++) {
          cout << rvec.at(i) << " ";
       }
       cout << endl;
       cout << "sum range (" << p << "," << q << ")" << endl;
       for (int i = 0; i < sum.size(); i++) {
          cout << sum.at(i) << " ";
       }
       cout << endl;
    }

    int merge(vector<long int>&sum, int p, int q) const {
       // No need to check for single elements since
       // boundary condition sum deltas will take care of this.
       if (p >= q) {
          return 0;
       }
#ifdef DEBUG
       print_range(sum, p, q);
#endif
       // result
       int count = 0;
       int mid = p + (q - p)/2;
       for (int i = p, j = mid + 1, k = mid + 1; i <= mid; i++) {
          while ((j <= q) && (sum.at(j) - sum.at(i)) < rmin) j++;
          while ((k <= q) && (sum.at(k) - sum.at(i)) <= rmax) k++;
          count+=(k - j);
#ifdef DEBUG
          cout << sum.at(i) << ":" << j << "," << k << "count : " << count << endl;
#endif
       }
       //C++ Merge function:
       //Merge the sorted paritioned sums. Note elements outside
       //the range remain unsorted in the prefix sum. Also note
       //how do we mark the end end iterator of q + 1, thats exclusive
       inplace_merge(sum.begin() + p, sum.begin() + mid + 1, sum.begin() + q + 1);
       return count;
    }

    int count_range(vector<long int>&sum, int p , int q) {
       if (p >= q) {
          return 0;
       } else {
          int mid = p + (q - p)/2;
          return count_range(sum, p, mid) + count_range(sum, mid + 1, q) +
             merge(sum, p, q);
       }
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
       rmin = lower;
       rmax = upper;
       rvec = nums;

       // build the sum prefix array
       vector<long int> sum{0}; // prefix sum
       for (auto i : nums) {
          sum.push_back(i + sum.back());
       }
       // Note we are passing the prefix sum vector and its index limits
       return count_range(sum, 0, sum.size() - 1);
    }
};

int main(void) {
#if 1
   //vector<int> v {1, 4, 2, 3, 6, -2, 0};
   //vector<int> v {0, 0, 0, 0, 0};
   vector<int> v {-2147483647,0,-2147483647,2147483647};
   Solution sol;
   cout << "Max Subarrays : " << sol.countRangeSum(v, 4, 6) << endl;
   cout << "Max Subarrays : " << sol.countRangeSum(v, 0, 0) << endl;
   cout << "Max Subarrays : " << sol.countRangeSum(v, 4, 5) << endl;
   cout << "Max Subarrays : " << sol.countRangeSum(v, -564, 3864) << endl;
#endif
   return 0;
}
