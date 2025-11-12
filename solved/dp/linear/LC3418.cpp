/**
 * @Time : 2025/1/12-8:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3418 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size(), m = coins[0].size();
        vector<vector<vector<int>>> dp(n + 1, vector(m + 1, vector(3, (int)-1e9)));
        dp[0][1][0] = dp[1][0][0] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                int c = coins[i - 1][j - 1];
                for(int k = 0; k <= 2; k++) {
                    dp[i][j][k] = max(dp[i-1][j][k], dp[i][j-1][k]) + c;
                    if(k > 0)
                        dp[i][j][k] = max({dp[i][j][k], dp[i-1][j][k-1], dp[i][j-1][k-1]});
                }
            }
        }
        return max({dp[n][m][2], dp[n][m][1], dp[n][m][0]});
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}