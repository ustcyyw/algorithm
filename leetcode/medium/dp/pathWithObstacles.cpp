/**
 * @Time : 2022/6/3-10:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 执行用时：4 ms, 在所有 C++ 提交中击败了98.22%的用户
 * 内存消耗：8.5 MB, 在所有 C++ 提交中击败了97.96%的用户
 */

class Solution {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if(grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return {};
        grid[0][0] = 2;
        for(int i = 1; i < n && grid[0][i] == 0; i++)
            grid[0][i] = 2;
        for(int i = 1; i < m && grid[i][0] == 0; i++)
            grid[i][0] = 2;
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                if(grid[i][j] != 1 && (grid[i - 1][j] == 2 || grid[i][j - 1] == 2))
                    grid[i][j] = 2;
            }
        }
        if(grid[m - 1][n - 1] != 2) return {};
        vector<vector<int>> path = vector(m + n - 1, vector(2, 0));
        for(int i = m - 1, j = n - 1; i + j > 0; ){
            vector<int>& cur = path[i + j]; // 注意要使用引用
            cur[0] = i, cur[1] = j;
            if(i > 0 && grid[i - 1][j] == 2) i--;
            else j--;
        }
        return path;
    }
};

int main(){
    Solution s;
    vector<vector<int>> grid = {{0,0}};
    s.pathWithObstacles(grid);
}