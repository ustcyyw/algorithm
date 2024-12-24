/**
 * @Time : 2024/12/23-9:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3393 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<ll>>> dp(n + 1, vector(m + 1, vector(32, 0ll)));
        dp[1][1][grid[0][0]] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(i == 1 && j == 1) continue;
                int num = grid[i - 1][j - 1];
                for(int x = 0; x <= 16; x++) {
                    dp[i][j][x] = (dp[i-1][j][x ^ num] + dp[i][j-1][x ^ num]) % mod;
                }
            }
        }
        return dp[n][m][k];
    }
};