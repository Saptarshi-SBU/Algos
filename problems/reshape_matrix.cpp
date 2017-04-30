#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:

    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {

        if (nums.empty()) {
            return vector<vector<int>>();
        }

        int row = nums.size();
        int col = nums.at(0).size();
        int nr = row * col;
        if (nr < r*c) {
            return nums;
        }

        // Fix : Initialize vector
        vector<vector<int>> result(r);
        for (int i = 0, p = 0, q = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                assert (p < row);
                assert (q < col);
                // Fix : [][] does not not do causes access bound check
                // So can hit access violation if vector is not initilized
                result[i].push_back(nums[p][q]);
                q = (q + 1) % col;
                p = q ? p : p + 1;
            }
        }
        return result;
    }
};

int main(void) {
    vector<vector<int>> nums = { {1,2}, {3,4}};
    Solution sol;
    auto vec = sol.matrixReshape(nums, 1, 4);
    cout << vec.size() << endl;
    return 0;
}
