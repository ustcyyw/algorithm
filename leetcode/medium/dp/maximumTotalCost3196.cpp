/**
 * @Time : 2024/6/30-3:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : lc3196 周赛403 t3 线性动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumTotalCost(vector<int>& nums) {
        int n = nums.size();
        vector<long long> dp(n + 1, 0ll);
        dp[1] = nums[0];
        for(int i = 2; i <= n; i++) {
            int cur = nums[i - 1], pre = nums[i - 2];
            dp[i] = max(dp[i - 1] + cur, dp[i - 2] + pre - cur);
        }
        return dp[n];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}