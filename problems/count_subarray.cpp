/*-----------------------------------------------------------------------------
 *
 *  Copyright (C), 2017 Saptarshi Sen
 *
 *  Compute number of sub-arrays with sum K
 *
 *  Algorithm : MergeSort
 *  --------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int toMatch;

    int subarraySumMerge(vector<int>&sum, int p, int q) {
        if (p >= q) {
            return 0;
        }

        int mid = p + (q - p)/2;
        int i = p;
        int j = mid + 1;
        int k = mid + 1;
        int count = 0;
        for (;i <= mid; i++) {
            while ((j <= q) && (sum[j] - sum[i]) < toMatch) j++;
            while ((k <= q) && (sum[k] - sum[i]) <= toMatch) k++;
            count+=(k - j);
        }

        inplace_merge(sum.begin() + p, sum.begin() + mid + 1,  sum.begin() + q + 1);
        return count;
    }

    int subarraySumMergeSort(vector<int>&sum, int p, int q) {
        if (p >= q) {
            return 0;
        } else {
            int mid = p + (q - p)/2;
            return subarraySumMergeSort(sum, p, mid) +
                subarraySumMergeSort(sum, mid + 1, q) +
                subarraySumMerge(sum, p, q);
        }
    }

    int subarraySum(vector<int>& nums, int k) {
        toMatch = k;
        if (nums.empty()) {
            return 0;
        }
        vector<int> sum{0};
        for (auto i : nums) {
            sum.push_back(i + sum.back());
        }
        return subarraySumMergeSort(sum, 0, sum.size() - 1);
    }
};

int main(void) {
    vector<int> v{1,1,1};
    Solution sol;
    cout << sol.subarraySum(v, 2) << endl;
    return 0;
}
