/**
 * @Time : 2022/6/30-1:16 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp = vector(m, vector(n, 100000));
        dp[0].assign(n, 0); // 与第20行一起看，保证了起点的路径代价就是该点的数值
        for(int i = 0; i < m - 1; i++){
            for(int j = 0; j < n; j++){ // 从i，j这个点出发到i+1层的点
                int val = grid[i][j];
                dp[i][j] += val; // 路径代价还要加上该点的数值，然后才开始走下一层的路径
                vector<int> cost = moveCost[val];
                for(int k = 0; k < n; k++){
                    dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + cost[k]);
                }
            }
        }
        int res = 1100000;
        for(int i = 0; i < n; i++)
            res = min(res, dp[m - 1][i] + grid[m - 1][i]);
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> grid = {{5,3},{4,0},{2,1}}, moveCost = {{9,8},{1,5},{10,12},{18,6},{2,4},{14,3}};
    s.minPathCost(grid, moveCost);
    cout << 0 << endl;
}