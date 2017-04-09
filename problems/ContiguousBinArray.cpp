/*----------------------------------------------------------------------------

  Find contiguos sub-array having equal number of zeros and ones

  https://leetcode.com/submissions/detail/99604501/

  O(n) Solution based on Zero Sum or Non-Zero sum reoccurence

-----------------------------------------------------------------------------*/

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {

public:

    // Brute Force O(n^2)
    int findMaxLengthI(vector<int>& nums) {
        if (nums.empty())
           return 0;

        int maxLen;
        for (int i = 0; i < nums.size(); i++) {
           int p = 0;
           int q = 0;
           for (int j = i; j < nums.size(); j++) {
               if (nums.at(j)) p++; else q++;
               if ((p == q) && (maxLen < p + q)) maxLen = p + q;
           }
        }
        return maxLen;
    }
    
    // O (n)
    int findMaxLengthII(vector<int>& nums) {

        int maxLen = 0;

        // modify array replace 0's with -1. To help sum figure out any pairs    
        for_each (nums.begin(), nums.end(), [] (int& i) { if (!i) i = -1;});

        int sum = 0;
        unordered_map<int, int> hashMap; // store position of first occurence of sum

        for (int i = 0; i < nums.size(); i++) {

            sum+=nums.at(i);

            //Case : Zero sum is a special case indicating contiguous array from pos 0
            //Case : Non-Zero sum, check when it re-occurs
            if (!sum || (hashMap.find(sum) == hashMap.end())) { 
                hashMap[sum] = i;
            }    

            // Zero-Sum
            if (!sum) {   
               maxLen = max(maxLen, hashMap[sum] + 1);
            // Non Zero-Sum Re-occur  
            } else {
               maxLen = max(maxLen, i - hashMap[sum]);
            }   
        }    
        return maxLen;
    }
};

int main(void) {
    vector<int> v = { 1, 0, 1, 0, 1, 1};
    Solution sol;  
    cout << "Result " << sol.findMaxLengthII(v) << endl;
    return 0;
}
