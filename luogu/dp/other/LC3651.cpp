/**
 * @Time : 2025/10/29-17:17
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3651 2411 动态规划 前缀优化
 */
 /*
  * dp[i][j][k]: 到(x,y)点并且使用了k次移动的最小cost
  * 1. dp[x][y][k-1] 转移过来 并且 gird[x][y] >= grid[i][j]
  * 上一层的状态 可以排序之后记录一个后缀最小值
  * 2. dp[i][j-1][k] + cost
  * 3. dp[i-1][j][k] + cost
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m, sz;
    vector<vector<int>> rank;
    int minCost(vector<vector<int>>& grid, int K) {
        init(grid);
        vector<vector<vector<int>>> dp(n, vector(m, vector(K + 1, INT_MAX)));
        dp[0][0][0] = 0;
        vector<vector<int>> suf(K + 1, vector(sz, INT_MAX));
        int ans = INT_MAX;
        for(int k = 0; k <= K; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    int rk = rank[i][j];
                    if(k > 0) dp[i][j][k] = suf[k - 1][rk];
                    if(j > 0) dp[i][j][k] = min(dp[i][j][k], dp[i][j-1][k] + grid[i][j]);
                    if(i > 0) dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k] + grid[i][j]);
                    suf[k][rk] = min(suf[k][rk], dp[i][j][k]);
                    if(i == n - 1 && j == m - 1)
                        ans = min(ans, dp[i][j][k]);
                }
            }
            for(int i = sz - 2; i >= 0; i--)
                suf[k][i] = min(suf[k][i], suf[k][i + 1]);
        }
        return ans;
    }

    void init(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        rank.assign(n, vector(m, 0));
        vector<int> pos;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                pos.push_back(grid[i][j]);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        sz = pos.size();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                rank[i][j] = lower_bound(pos.begin(), pos.end(), grid[i][j]) - pos.begin();
        }
    }
};