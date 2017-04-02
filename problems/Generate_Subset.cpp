/*------------------------------------------------------------------------
 *
 * Copyright(C) : 2017, Saptarshi Sen
 * 
 * Generate Possible Subsets : Power Set (2^n)
 *
 * https://leetcode.com/submissions/detail/98891272/
 *
 * ----------------------------------------------------------------------*/
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            // Result stored
            vector<vector<int>> result;

            GenerateSubset(nums, result);

            // Empty Set
            result.push_back(vector<int>());

            return result;
        }

        void GenerateSubset(vector<int> nums, vector<vector<int>>& result) {
            if (nums.empty())
                return;

            int curr = nums.back();

            // Create subsets from previous subsets 
            // by appending current element
            vector<vector<int>> subset; 
            for (auto i : result) {
               i.push_back(curr);
               subset.push_back(i);
            }    

            // Finally include standalone current element
            // in the subset 
            subset.push_back(vector<int> { curr });

            // Update result with the new subset
            for (auto i : subset)
               result.push_back(i);

            // Move on to the next element for Next Subset computation
            nums.pop_back(); 

            GenerateSubset(nums, result);
        }

        void OutputResult(vector<vector<int>>& result) const {
           cout << "Subsets :" << endl;
           for (auto i : result) {
               bool next = false;
               if (i.empty()) {
                  cout << "{ }" << endl;
                  continue;
               }

               cout << "{";
               for (auto j : i) {
                  if (next) cout << ",";
                  cout << j;
                  next = true;
               }
               cout << "}" << endl;
            }
        }
};

int main(void) {
    Solution sol;
    //vector<int> v = {1,2};
    //vector<int> v = {1,2,3};
    //vector<int> v = {1,2,3,4};
    //vector<int> v = {1,2,3,4,5,6};
    vector<int> v = {};
    auto ans = sol.subsets(v);
    sol.OutputResult(ans);
    cout << "Total elements :" << v.size() 
         << " Total subsets :" << ans.size() << endl;
    return 0;
}
