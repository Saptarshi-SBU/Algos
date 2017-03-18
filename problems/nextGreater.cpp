/*----------------------------------------------------------------------------
 * Copyright(C) : 2017, Saptarshi Sen
 *
 * Next Greater element I
 *
 * Algorithm : Using stack maintain all possible greater numbers for an element
 *             in the list. O(n)
 *
 * https://leetcode.com/submissions/detail/96955181/
 *
 * Next Greater element II (Circular, may contain duplicate elements)
 *
 * Algorithm : Using window to store all possible greater numbers, update window
 *             in circular fashion while searching for the next greater. O(n)
 *
 *
 * https://leetcode.com/submissions/detail/97137821/
 *
 * ---------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {

public:

    // No duplicate elements
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        stack<int> s; // to store all greater elements following n
        unordered_map<int, int> map; // to store next greater element

        if (findNums.empty())
           return vector<int>();

        for (auto iter = nums.rbegin(); iter != nums.rend(); iter++) {
               while (!s.empty()) {
                   // element lesser is flushed
                   if (*iter > s.top()) {
                       s.pop();
                   // element can be candidate for previous
                   } else {
                       map[*iter] = s.top();
                       s.push(*iter);
                       break;
                   }
               }

               if (s.empty()) {
                  map[*iter] = -1;
                  s.push(*iter);
               }
        }

        vector<int> ans;
        for (auto iter = findNums.begin(); iter != findNums.end(); iter++) {
           if (map.find(*iter) != map.end()) {
              ans.push_back(map[*iter]);
           // if num not in parent vector
           } else {
              ans.push_back(-1);
           }
        }
        return ans;
     }

     // Circular : Store next greater elements in window
     vector<int> nextGreaterElements(vector<int>& nums) {
        deque<int> dq; // window
        vector<int> ans; // store next greater element

        if (nums.empty())
           return vector<int>();

        // Initialize window of next greater entries
        for (auto iter = nums.begin(); iter != nums.end(); iter++) {
           if (dq.empty() || (dq.back() < *iter)) {
              dq.push_back(*iter);
           }     
        }     

#if DEBUG
        cout << "dq size :" << dq.size() << endl;      
#endif       

        // Find Next Greater entry
        for (auto iter = nums.rbegin(); iter != nums.rend(); iter++) {
           // remove current element if in window 
           if (dq.back() == *iter) {
              dq.pop_back();
           }

           // search in the window 
           while (!dq.empty()) { 
              // Found 
              if (dq.front() <= *iter) {
                 dq.pop_front();
              } else {
                 ans.push_back(dq.front());
                 dq.push_front(*iter);
                 break;
              }
           }    

           // no greater entry found
           if (dq.empty()) {
              ans.push_back(-1);
              dq.push_front(*iter);
           }
        }

        // we update ans in reverse order
        std::reverse(ans.begin(), ans.end()); 
        return ans;
     }
};

int main(void) {
    vector<int> nums = {1,3,4,2};
    vector<int> subset = {4,1,2};
    Solution sol;
    auto vec = sol.nextGreaterElement(subset, nums);
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
       cout << *iter << " " << endl;

    vector<int> rnums01 = {5,3,10,2,0,8};
    vector<int> rnums02 = {1,2,1};
    vector<int> rnums03 = {100,1,11,1,120,111,123,1,-1,-100};
    vec = sol.nextGreaterElements(rnums03);
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
       cout << *iter << " " << endl;
    return 0;
}
