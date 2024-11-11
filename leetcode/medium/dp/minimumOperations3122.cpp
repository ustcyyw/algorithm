/**
 * @Time : 2024/4/28-10:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛394 t3 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> rowC(m + 1, vector(11, 0));
        for(int i = 1; i <= m; i++) { // 预处理每一列各个数字出现的次数
            for(int j = 0; j < n; j++)
                rowC[i][grid[j][i - 1]]++;
        }
        // dp[i][j]:第i列全为数字j的最小操作次数 10表示其它任意整数
        vector<vector<int>> dp(m + 1, vector(11, 0));
        for(int i = 1; i <= m; i++) {
            for(int j = 0; j <= 10; j++) {
                int temp = INT_MAX; // 截止前一列的最小操作次数 并且前一列不能和当前列的数字j相同
                for(int k = 0; k <= 10; k++) {
                    if(k != j) temp = min(temp, dp[i - 1][k]);
                }
                dp[i][j] = temp + n - rowC[i][j]; // 注意j=10时， rowC[i][j] = 0，表示需要将这一列所有数字都操作
            }
        }
        int ans = INT_MAX;
        for(int i = 0; i <= 10; i++)
            ans = min(dp[m][i], ans);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}