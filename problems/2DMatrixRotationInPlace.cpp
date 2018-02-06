/*-----------------------------------------------------------------------------
 * Copyright (C) 2018, Saptarshi Sen
 *
 * 2D Square Matrix Rotation by 90
 *
 * Algorithm : Apply Matrix Transformations
 *     a) Swap elements diagonalwise
 *     b) Reverse elements columnwise
 *
 * All rotations are composite reflections
 * (in fact, all transformations are composite reflections)
 *
 * https://leetcode.com/submissions/detail/139675694/
 *
 * ---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    void swap(int& a, int& b) {
        int sum = (a + b);
        a = b;
        b = sum - a;
    }

    void transform_diagonal(vector<vector<int>>& matrix) {
        int m = matrix.at(0).size();
        int n = matrix.size();

        assert (m == n);

        // Upper Half
        for (int pr = 0, pc = 0, qc = n - 1, qr = n - 1; pr < qr; pc++, qr--) {
            int p = pr, q = qr, i = pc, j = qc;
            while (p < q) {
                swap(matrix.at(p).at(i), matrix.at(q).at(j));
                p++;
                i++;
                q--;
                j--;
            }
        }

        // Lower Half
        for (int pr = n - 1, pc = 0, qr = n - 1, qc = 0; qc < n - 1; pr--, qc++) {
            int p = pr, q = qr, i = 0, j = qc;
            while (p < q) {
                swap(matrix.at(p).at(i), matrix.at(q).at(j));
                p++;
                i++;
                q--;
                j--;
            }
        }
    }

    void transform_reverse(vector<vector<int>>& matrix) {
        int n = matrix.size();
	// reverse columnwise
        for (int pr = 0, pc = 0; pc < n; pc++)  {
            int p = pr, q = n - 1, i = pc, j = pc;
            while (p < q) {
                swap(matrix.at(p).at(i), matrix.at(q).at(j));
                p++;
                q--;
            }
        }
    }

    void rotate(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return;
        }
        transform_diagonal(matrix);
        transform_reverse(matrix);
    }

    void rotateFaster(vector<vector<int> > &matrix) {
        transform_reverse(matrix);
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = i + 1; j < matrix[i].size(); ++j)
                swap(matrix[i][j], matrix[j][i]);
        }
    }
};

int main(void) {
    Solution sol;
    vector<vector<int>> matrix = {{1,2,3}, {3,4,1}, {5,6,7}};
    sol.rotate(matrix);
    sol.rotateFaster(matrix);
    return 0;
}
