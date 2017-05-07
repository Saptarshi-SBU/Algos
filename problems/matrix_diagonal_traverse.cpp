/*-----------------------------------------------------------------------------
 * Copyright (C) 2017, Saptarshi Sen
 *
 * Matrix Diagonal Traversal : Walk Based
 *
 * https://leetcode.com/submissions/detail/102223687/
 * ---------------------------------------------------------------------------*/
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {

public:

    // Algorithms :
    // We tried a couple of algorithms, trying to achieve zig-zag traversal
    // A) One was for only square matrix based on two sets of zig-zag iteration :
    // one for upper diagonal matrix, other for lower diagonal matrix
    // B) The second one is based on a state machine governing the traversal.
    // The state machine based traversal is generic in nature.

    enum direction {
        INIT = 0,
        RIGHT,
        ZIG,
        DOWN,
        ZAG,
        END
    };

    const vector<string> dbgstr = { "INIT", "RIGHT", "ZIG", "DOWN", "ZAG", "END"};

    int dbg = 0;

    #define PRINT(x,y, state) if (dbg) cout << x << ":" << y << state << endl

    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {

        vector<int> result;

        // Corner Case
        if (matrix.empty()) {
            return result;
        }

        int nr_rows = matrix.size();
        int nr_cols = matrix.at(0).size();

        int i = 0, j = 0;

        direction dir = INIT;

        while (result.size() < nr_rows*nr_cols) {
            switch (dir) {
                case INIT:
                    result.push_back(matrix[i][j]);
                    PRINT(i, j, dbgstr[dir]);
                    dir = (j < nr_cols - 1) ?  RIGHT : DOWN;
                    break;

                case RIGHT:
                    j++;
                    assert (j < nr_cols);
                    PRINT (i, j, dbgstr[dir]);
                    dir = (i < nr_rows - 1) ? ZIG : ZAG;
                    break;

                case DOWN:
                    i++;
                    assert (i < nr_rows);
                    PRINT (i, j, dbgstr[dir]);
                    dir = (j == 0) ? ZAG :  ZIG;
                    break;

                case ZIG:
                    // Diagonal traversal
                    // Note : use of only a single loop
                    for (;i < nr_rows && j >= 0; i++, j--) {
                        result.push_back(matrix[i][j]);
                        PRINT(i, j, dbgstr[dir]);
                        if (i >= nr_rows - 1) break;
                        if (j <= 0) break;
                    } 

                    // Boundary condition
                    if (i < nr_rows - 1) dir = DOWN;
                    else if (j < nr_cols - 1) dir = RIGHT;
                    else dir = END;
                    break;

                case  ZAG:
                    // Diagonal traversal
                    // Note : use of only a single loop
                    for (;i >=0 && j < nr_cols; i--, j++) {
                        result.push_back(matrix[i][j]);
                        PRINT(i, j, dbgstr[dir]);
                        if (i <= 0) break;
                        if (j >= nr_cols - 1) break;
                    }

                    // Boundary condition
                    if (j < nr_cols - 1) dir = RIGHT;
                    else if (i < nr_rows - 1) dir = DOWN;
                    else dir = END;
                    break;

                case END:
                    assert (result.size() == nr_rows*nr_cols);
                    PRINT (i, j, dbgstr[dir]);
                    break;

                default :
                    assert(0);
            }
        }
        return result;
    }
};

int main(void) {
   vector<vector<int>> v =  { {1,2,3}, {4,5,6}, {7,8,9} };
   Solution sol;
   auto vec = sol.findDiagonalOrder(v); 
   for (auto i : vec)
      cout << i << " ";
   cout << endl;
   return 0;
}

