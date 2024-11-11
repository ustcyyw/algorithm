/**
 * @Time : 2022/7/7-2:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。

对于每个单元格，你可以往上，下，左，右四个方向移动。 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。

 

示例 1：



输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
输出：4
解释：最长递增路径为 [1, 2, 6, 9]。
示例 2：



输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
输出：4
解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。
示例 3：

输入：matrix = [[1]]
输出：1
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 231 - 1
 

注意：本题与主站 329 题相同： https://algorithm-cn.com/problems/longest-increasing-path-in-a-matrix/

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/fpTFWP
 */
class Solution {
public:
    /**
     * 执行用时：36 ms, 在所有 C++ 提交中击败了90.16%的用户
     * 内存消耗：15.6 MB, 在所有 C++ 提交中击败了62.11%的用户
     */
    int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
    vector<vector<int>> cache;
    int m, n;
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int res = -0x7FFFFFFF;
        m = matrix.size(), n = matrix[0].size();
        cache.assign(m, vector(n, 0));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                res = max(res, dfs(matrix, i, j));
            }
        }
        return res;
    }

    int dfs(vector<vector<int>>& matrix, int x, int y){
        if(cache[x][y]) return cache[x][y];
        int len = 1;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= m || ny >= n || matrix[nx][ny] >= matrix[x][y])
                continue;
            len = max(len, dfs(matrix, nx, ny) + 1);
        }
        cache[x][y] = len;
        return len;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}