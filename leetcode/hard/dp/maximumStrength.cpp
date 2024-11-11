/**
 * @Time : 2024/3/10-3:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛388 t4
 */
/*
 * 题目提示 n*k < 1e6 并且容易想到dp
 * dp[i][j]: 截止第i个元素 选取了j个子数组的最大值（下标从1开始 方便处理边界状态）
 * 在计算状态时 容易想到 dp[i][j] = max{dp[i - 1][j], temp}
 * 其中 temp = max{dp[lo-1][j-1] + sum[lo,i] * C[j]}, for lo in [1, i]
 * 表示枚举包括nums[i]的子数组 将其作为第j个子数组
 * 对lo进行遍历 会超时 但如果每个状态可以o1地转移 一共n*k个状态 可以求解。
 * 所以想到dp优化
 * dp[lo-1][j-1] + sum[lo,i] * C[j]
 * = dp[lo-1][j-1] + (sum[i] - sum[lo-1]) * C[j]
 * = dp[lo-1][j-1] - sum[lo-1] * C[j] + sum[i] * C[j]
 * 在计算dp[i][j]时: 在确定i和j的情况下
 * sum[i] * C[j]是一个确定的值, j-1和C[j]是定值
 * 式子中唯一变量是t = lo - 1，范围[0, i-1]
 * 关键在于计算 dp[lo-1][j-1] - sum[lo-1] * C[j]，for lo in [1, i] 的最大值
 * 记 pre[i][j] 表示j确定的情况下 max(dp[lo-1][j] - sum[lo-1] * C[j+1])
 * 那么 dp[i][j] = max(dp[i - 1][j], pre[i-1][j-1])
 * 计算过程中维护pre[i][j]，就能实现o1地更新状态
 *
 * 边界条件：j = 0时的计算
 * 此时表示不选取任何子数组，因此 dp[i][0] = 0
 * pre[i][0] = max(pre[i - 1][0], dp[i][0] - sum[i] * C[1])
 * = max(pre[i - 1][0], -sum[i] * C[1])
 * 特别地 pre[0][0] = sum[0] * C[1] = 0
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MIN_VAL = -1e18;

class Solution {
public:
    long long maximumStrength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> sum(n + 1, 0), C(k + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        for(int i = 1, temp = 1; i <= k; i++, temp *= -1)
            C[i] = temp * (k - i + 1);
        vector<vector<ll>> dp(n + 1, vector(k + 1, MIN_VAL)), pre(n + 1, vector(k, MIN_VAL));
        dp[0][0] = pre[0][0] = 0;
        for(int i = 1; i <= n; i++)
            dp[i][0] = 0, pre[i][0] = max(pre[i - 1][0], -C[1] * sum[i]);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= k; j++) {
                dp[i][j] = max(dp[i - 1][j], pre[i - 1][j - 1] + C[j] * sum[i]);
                if(j < k) pre[i][j] = max(pre[i - 1][j], dp[i][j] - C[j + 1] * sum[i]);
            }
        }
        return dp[n][k];
    }
};