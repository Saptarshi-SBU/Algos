/*------------------------------------------------------------------------
 *
 * Copyright(C) : 2017, Saptarshi Sen
 * 
 * Generate Possible Subsets : Power Set 
 *
 * Note : The subsets are distinct
 *
 * Noduplictaes : https://leetcode.com/submissions/detail/98891272/ (2^N)
 *
 * Duplicates : https://leetcode.com/submissions/detail/98921691/
 *
 * ----------------------------------------------------------------------*/
#include <vector>
#include <unordered_map>
#include <iostream>

#define NODUPLICATES 0

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

        // Treat Multiple Occurences as ONE and then add them to existing 
        // subset entries.(and then expand)
        vector<vector<int>> subsetsForDuplicates(vector<int>& nums) {

            // Result stored
            vector<vector<int>> result;

            // map for duplicates
            unordered_map<int, int> freq;

            // for duplicates
            for (auto& i : nums) {
               freq[i] = (freq.find(i) == freq.end()) ? 1 : freq[i] + 1;
            }   

            // for all unique elements
            for (auto& i : freq) {
               // possible subsets from current element
               vector<vector<int>> subset;
           
               // vector with occurences of current element 
               vector<int> curr;
               for (int count = 0; count < i.second; count++) {
                   curr.push_back(i.first);
                   subset.push_back(curr);
               }

               // create subsets from previous entries
               for (auto entry : result) {
                  for (auto j : curr) {
                     entry.push_back(j);
                     subset.push_back(entry);
                  }
               }

               // update result with computed subsets
               for (auto& k : subset)
                  result.push_back(k);
            }

            // empty Set
            result.push_back(vector<int>());

            return result;
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
    //vector<int> v = {};
    vector<int> v = {1,1,1,2,2};
#if NODUPLICATES
    auto ans = sol.subsets(v);
#else
    auto ans = sol.subsetsForDuplicates(v);
#endif    
    sol.OutputResult(ans);
    cout << "Total elements :" << v.size() 
         << " Total subsets :" << ans.size() << endl;
    return 0;
}
