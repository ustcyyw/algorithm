/**
 * @Time : 2022/8/18-3:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 二维矩阵 grid 由 0 （土地）和 1 （水）组成。岛是由最大的4个方向连通的 0 组成的群，封闭岛是一个 完全 由1包围（左、上、右、下）的岛。

请返回 封闭岛屿 的数目。

 

示例 1：



输入：grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
输出：2
解释：
灰色区域的岛屿是封闭岛屿，因为这座岛屿完全被水域包围（即被 1 区域包围）。
示例 2：



输入：grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
输出：1
示例 3：

输入：grid = [[1,1,1,1,1,1,1],
             [1,0,0,0,0,0,1],
             [1,0,1,1,1,0,1],
             [1,0,1,0,1,0,1],
             [1,0,1,1,1,0,1],
             [1,0,0,0,0,0,1],
             [1,1,1,1,1,1,1]]
输出：2
 

提示：

1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-closed-islands
 */
class Solution {
public:
    /**
     * 执行用时：8 ms, 在所有 C++ 提交中击败了94.33%的用户
     * 内存消耗：9.3 MB, 在所有 C++ 提交中击败了27.49%的用户
     */
    int n, m;
    int dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
    int closedIsland(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        for(int i = 0; i < n; i++){
            if(grid[i][0] == 0) backTrack(grid, i, 0);
            if(grid[i][m - 1] == 0) backTrack(grid, i, m - 1);
        }
        for(int i = 0; i < m; i++){
            if(grid[0][i] == 0) backTrack(grid, 0, i);
            if(grid[n - 1][i] == 0) backTrack(grid, n - 1, i);
        }
        int res = 0;
        for(int i = 1; i < n - 1; i++){
            for(int j = 1; j < m - 1; j++){
                if(grid[i][j] == 0){
                    res++;
                    backTrack(grid, i, j);
                }
            }
        }
        return res;
    }

    void backTrack(vector<vector<int>>& grid, int x, int y){
        grid[x][y] = 1;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] != 0) continue;
            backTrack(grid, nx, ny);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}