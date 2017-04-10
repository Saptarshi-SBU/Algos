/*-----------------------------------------------------------------------------
 *
 * Copyright (C) 2017 Saptarshi Sen
 *
 * Compute Number of Friend Circles : O(n2)
 *
 * https://leetcode.com/contest/leetcode-weekly-contest-26/submissions/detail/99645905/
 *
 * ---------------------------------------------------------------------------*/

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {

public:
 
    // Return a unique friend circle if search succedds
    int dfs(int i, vector<vector<int>>& M) {
       int index = 0;
       queue<int> q; // store all direct friends of i
       for_each(M.at(i).begin(), M.at(i).end(), [&q, index] (const int& val) mutable
          { 
             if (val)
                q.push(index);
             index++;
          });
#      ifdef DEBUG
       cout << "index : " << i << " list size : " << q.size() << endl;  
#      endif      
       //entries already belong to an existing circle
       if (q.empty()) {
          return false;
       }

       while (!q.empty()) {
          M[i][q.front()] = 0;
          dfs(q.front(), M);
          q.pop();
       }
       return true;
    }

    int findCircleNum(vector<vector<int>>& M) {
       int row = 0;  
       int nr_fcircle = 0;
       for (int i = 0; i < M.size(); i++) {
           // Mark Clean all friends in this DFS search
           if (dfs(i, M)) {
              nr_fcircle++;
           }   
       }    
       return nr_fcircle;
    }
};

int main(void) {

    vector<vector<int>> M;
#if 1 
    M.push_back(vector<int>{1, 1, 0}); 
    M.push_back(vector<int>{1, 1, 0}); 
    M.push_back(vector<int>{0, 0, 1}); 
#endif    
    Solution sol;
    cout << "Result : " << sol.findCircleNum(M) << endl;
    return 0;
}
