/**
 * @Time : 2022/12/9-9:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * dp[i][j] 走了i步，拿取了nums中最左边j个数字的最大分数
     * dp[0][0] = 0;
     *
     */
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int m = multipliers.size(), n = nums.size(), res = INT_MIN;
        vector<vector<int>> dp(m + 1, vector(m + 1, INT_MIN));
        dp[0][0] = 0;
        for(int i = 1; i <= m; i++){
            int mul = multipliers[i - 1];
            dp[i][0] = dp[i - 1][0] + mul * nums[n - i];
            dp[i][i] = dp[i - 1][i - 1] + mul * nums[i - 1];
            for(int j = 1; j < i; j++)
                dp[i][j] = max(dp[i - 1][j] + mul * nums[n - i + j], dp[i - 1][j - 1] + mul * nums[j - 1]);
        }
        for(int i = 0; i <= m; i++)
            res = max(res, dp[m][i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}