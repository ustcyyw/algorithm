/**
 * @Time : 2025/9/29-16:34
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, T = 1e9;
/*
 * dp[i][0]: 截止i位置以1个奇数结尾
 * dp[i][1]: 截止i位置以2个奇数结尾
 * dp[i][2]: 截止i位置以1个偶数结尾
 * dp[i][3]: 截止i位置以2个偶数结尾
 */
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();
        vector<vector<ll>> dp(n, vector(4, 0ll));
        if(nums[0] % 2 == 1) dp[0][0] = 1;
        else dp[0][2] = 1;
        for(int i = 1; i < n; i++) {
            if(nums[i] % 2 == 1) {
                dp[i][1] = dp[i - 1][0];
                dp[i][0] = 1 + dp[i - 1][2] + dp[i - 1][3];
            } else {
                dp[i][3] = dp[i - 1][2];
                dp[i][2] = 1 + dp[i - 1][0] + dp[i - 1][1];
            }
            for(int j = 0; j < 4; j++)
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
        }
        return (dp[n - 1][0] + dp[n - 1][1] + dp[n - 1][2] +dp[n - 1][3]) % mod;
    }
};