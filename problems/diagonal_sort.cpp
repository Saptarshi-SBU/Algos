#include <map>
#include <vector>
#include <cassert>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
    std::map<std::pair<int, int>, std::vector<int>> map_diagonal;
    
    if (mat.empty())
        return vector<vector<int>>();
    
    int m = mat.size();
    int n = mat.at(0).size();
    
    for (int r = 0, c = 0; c < n; c++) {
        int i = 0, k = 0;
        auto key = std::pair<int, int>(0, c);
        map_diagonal.insert(std::pair<std::pair<int, int>, std::vector<int>>(key, std::vector<int>()));
        while (((r + k) < m) && ((c + k) < n)) {
            map_diagonal[key].push_back(mat[r + k][c + k]);
            k++;
        }
        std::sort(map_diagonal[key].begin(), map_diagonal[key].end());
        
        k = 0; 
        while (((r + k) < m) && ((c + k) < n)) {
            assert (i < static_cast<int>(map_diagonal[key].size()));
            mat[r + k][c + k] = map_diagonal[key][i];
            k++;
            i++;
        }
    }
    
    for (int r = 1, c = 0; r < m; r++) {
        int i = 0, k = 0;
        auto key = std::pair<int, int>(r, 0);
        map_diagonal.insert(std::pair<std::pair<int, int>, std::vector<int>>(key, std::vector<int>()));
        while (((r + k) < m) && ((c + k) < n)) {
            map_diagonal[key].push_back(mat[r + k][c + k]);
            k++;
        }   
        std::sort(map_diagonal[key].begin(), map_diagonal[key].end());

        k = 0;
        while (((r + k) < m) && ((c + k) < n)) {
            assert (i < static_cast<int>(map_diagonal[key].size()));
            mat[r + k][c + k] = map_diagonal[key][i];
            k++;
            i++;
        }
    }
    return mat;
}

int main(void) {
    //vector<vector<int>> matrix { {3,3,1,1}, {2,2,1,2}, {1,1,1,2}};
    //vector<vector<int>> matrix { {3,3,1,1}, {2,2,1,2}, {1,1,1,2}, {2,3,4,1} };
    //vector<vector<int>> matrix { {3,3,1}, {2,2,1}, {1,1,100} };
    vector<vector<int>> matrix { {3,3,1}, {2,2,1} };
    diagonalSort(matrix);
    for (auto &vec : matrix) {
        for (auto &v : vec) 
            std::cout << v << " ";
        std::cout << std::endl;
    }
    return 0;
}
