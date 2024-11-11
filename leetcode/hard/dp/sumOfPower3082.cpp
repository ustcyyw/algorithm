/**
 * @Time : 2024/3/24-8:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    /*
     * dp[i][j][k]: 截止到第i个元素 包含j个数且和为k的子序列的数目
     * 最终枚举子序列中元素的数目j，那么n-j就是不在该子序列中的元素
     * 这些元素每个都可以独立地添加或者不添加到此子序列中 都能保证新的序列中存在和为k的子序列
     */
    ll qp(ll a, ll b) {
        ll res = 1;
        while (b != 0){
            if((b & 1) == 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<vector<ll>>> dp(n, vector(n + 1, vector(k + 1, 0ll)));
        if(nums[0] <= k) dp[0][1][nums[0]] = 1;
        dp[0][0][0] = 1;
        for(int i = 1; i < n; i++) {
            dp[i][0][0] = 1;
            for(int j = 1; j <= n; j++) {
                for(int l = 1; l <= k; l++) {
                    dp[i][j][l] = dp[i - 1][j][l];
                    if(l - nums[i] >= 0)
                        dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j - 1][l - nums[i]]) % mod;
                }
            }
        }
        ll res = 0;
        for(int j = 1; j <= n; j++) {
            if(dp[n - 1][j][k] != 0)
                res = (res + qp(2, n - j) * dp[n - 1][j][k]) % mod;
        }
        return (int)res;
    }

    /*
     * dp[i][j]: 截止第i个元素 有多少个子序列t 且t中存在子序列和为j
     */
    int sumOfPower2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<ll>> dp(n + 1, vector(k + 1, 0ll));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for(int j = 0; j <= k; j++) {
                // num不放在子序列t中
                dp[i][j] = dp[i - 1][j];
                // num放在子序列t中 但可以不做为t的子序列元素
                dp[i][j] += dp[i - 1][j];
                // num放在子序列t中 那么做为t的子序列的元素
                if(j - num >= 0) dp[i][j] += dp[i - 1][j - num];
                dp[i][j] %= mod;
            }
        }
        return dp[n][k];
    }
};