/**
 * @Time : 2022/8/17-10:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 rows x cols 的矩阵 grid 来表示一块樱桃地。 grid 中每个格子的数字表示你能获得的樱桃数目。

你有两个机器人帮你收集樱桃，机器人 1 从左上角格子 (0,0) 出发，机器人 2 从右上角格子 (0, cols-1) 出发。

请你按照如下规则，返回两个机器人能收集的最多樱桃数目：

从格子 (i,j) 出发，机器人可以移动到格子 (i+1, j-1)，(i+1, j) 或者 (i+1, j+1) 。
当一个机器人经过某个格子时，它会把该格子内所有的樱桃都摘走，然后这个位置会变成空格子，即没有樱桃的格子。
当两个机器人同时到达同一个格子时，它们中只有一个可以摘到樱桃。
两个机器人在任意时刻都不能移动到 grid 外面。
两个机器人最后都要到达 grid 最底下一行。
 

示例 1：



输入：grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
输出：24
解释：机器人 1 和机器人 2 的路径在上图中分别用绿色和蓝色表示。
机器人 1 摘的樱桃数目为 (3 + 2 + 5 + 2) = 12 。
机器人 2 摘的樱桃数目为 (1 + 5 + 5 + 1) = 12 。
樱桃总数为： 12 + 12 = 24 。
示例 2：



输入：grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
输出：28
解释：机器人 1 和机器人 2 的路径在上图中分别用绿色和蓝色表示。
机器人 1 摘的樱桃数目为 (1 + 9 + 5 + 2) = 17 。
机器人 2 摘的樱桃数目为 (1 + 3 + 4 + 3) = 11 。
樱桃总数为： 17 + 11 = 28 。
示例 3：

输入：grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
输出：22
示例 4：

输入：grid = [[1,1],[1,1]]
输出：4
 

提示：

rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100 

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/cherry-pickup-ii
 */
class Solution {
public:
    /**
     * 与摘樱桃类似，找到共同点，就是每一次移动，机器人都在同一行
     * 但是两个机器人会在不同的列
     * dp[i][j1][j2]就表示到达第i行时，两个机器人在第j1,j2列能拿大的最大樱桃数目
     */
    int dx[3] = {-1, 1, 0};
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>> dp = vector(n, vector(m, vector(m, -1)));
        dp[0][0][m - 1] = grid[0][0] + grid[0][m - 1];
        for(int i = 1; i < n; i++){
            for(int j1 = 0; j1 < m; j1++){
                for(int j2 = 0; j2 < m; j2++){ // 计算dp[i][j1][j2]
                    for(int k1 = 0; k1 < 3; k1++){
                        int pj1 = j1 + dx[k1];
                        if(pj1 < 0 || pj1 >= m) continue;
                        for(int k2 = 0; k2 < 3; k2++){
                            int pj2 = j2 + dx[k2];
                            if(pj2 < 0 || pj2 >= m) continue;
                            dp[i][j1][j2] = max(dp[i][j1][j2], dp[i - 1][pj1][pj2]);
                        }
                    }
                    if(dp[i][j1][j2] != -1) // 注意 可能的所有转移情况讨论完后，还是-1，说明这个状态不可达
                        dp[i][j1][j2] += j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2];
                }
            }
        }
        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++)
                res = max(res,dp[n - 1][i][j]);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}