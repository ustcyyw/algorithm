/**
 * @Time : 2025/1/6-12:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3409 动态规划 前缀优化
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * dp[i][d]: 以i结尾的且当前绝对差值为d的最大值
     * 前面的数得是 nums[i] + d, nums[i] - d
     * 并且这些数结尾的绝对值要 >= d 找满足条件的最大值
     *
     * d从大往下计算 使用 aux[num][d]表示以值为num的元素结尾 并且末尾的差值 >= d的最大数量
     * 前置的数pre = num - d, num + d
     * 当 d > 0时，pre不等于num，使用的都是前置位置的计算结果
     * 当 d = 0时，pre = num, 但是转移用的aux[num][0]还没有更新 也是前置位置的计算结果
     */
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size(), m = 301, ans = 0;
        vector<vector<int>> dp(n, vector(m, 0)), aux(m, vector(m + 1, 0));
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            dp[i][300] = 1; // 表示只选当前这个数 那么其差值假定为300不影响
            for(int d = m - 1; d >= 0; d--) {
                int p1 = num - d, p2 = num + d;
                if(p1 >= 0) dp[i][d] = max(dp[i][d], aux[p1][d] + 1);
                if(p2 <= 300) dp[i][d] = max(dp[i][d], aux[p2][d] + 1);
                aux[num][d] = max(dp[i][d], aux[num][d + 1]);
                ans = max(ans, dp[i][d]);
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}