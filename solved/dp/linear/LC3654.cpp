/**
 * @Time : 2025/10/28-22:22
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3654 2038 动态规划 线性动态规划 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;
/*
 * 前缀和对k求mod，余数相同的时可以确定子数组和被k整除
 * 如果删除一个子数组，对后续前缀和对k取mod的值没有影响 因为删了的部分是k的倍数
 *
 * 截止到i元素的最小答案
 * dp[i] = dp[i - 1] + nums[i], nums[i]不删除的情况
 * dp[i] = min{dp[j]} for mod[i] = mod[j], 删除nums[j + 1, i]
 * 应该按mod进行分类 并且求最小值
 */
class Solution {
public:
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> dp(n + 1, 0), pre(k, LONG_LONG_MAX);
        pre[0] = 0;
        ll sum = nums[0];
        for(int i = 1; i <= nums.size(); i++) {
            sum += nums[i - 1];
            int m = sum % k;
            dp[i] = min(dp[i - 1] + nums[i - 1], pre[m]);
            pre[m] = min(dp[i], pre[m]);
        }
        return dp[n];
    }
};