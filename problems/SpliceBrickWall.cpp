/*------------------------------------------------------------------------------
 *
 *  Copyright (C) 2017 Saptarshi Sen
 *
 *  Splice vertically with minimum number of cuts
 *
 *  - O(n) Space Complexity O(n)
 *
 *  https://leetcode.com/submissions/detail/99654732/
 * ---------------------------------------------------------------------------*/

#include <vector>
#include <cassert>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {

public:

    int leastBricks(vector<vector<int>>& wall) {

        if (wall.empty())
           return 0;
          
        for(auto& v : wall) {
            int old = 0;
            for (auto& i : v) {
                i+=old;
                old = i;
            }
        }    
        
        for (auto& v : wall)
            v.pop_back();

        int maxCommon = 0;        
        unordered_map<int, int> hashMap;
        for (auto& v : wall) {
            for (auto& i : v) {
                if (hashMap.find(i) == hashMap.end()) 
                   hashMap[i] = 1;
                else
                   hashMap[i]++;

                if (maxCommon < hashMap[i])
                   maxCommon = hashMap[i];
            }
        }
        return wall.size() - maxCommon; 
    }

    void print(vector<vector<int>>& wall) {
        for (auto& v : wall) {
            for (auto& i : v) {
                cout << " ";
            }    
            cout << endl;
        }
    }
};

int main(void) {
   vector<vector<int>> M;
#if 1
   M.push_back(vector<int> {1,2,2,1});
   M.push_back(vector<int> {3,1,2});
   M.push_back(vector<int> {1,3,2});
   M.push_back(vector<int> {2,4});
   M.push_back(vector<int> {3,1,2});
   M.push_back(vector<int> {1,3,1,1});
#else
   M.push_back(vector<int> {2,3,2});
   M.push_back(vector<int> {1,6});
#endif   
   Solution sol;
   cout << sol.leastBricks(M) << endl;
   return 0;
}
