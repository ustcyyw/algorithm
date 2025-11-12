/**
 * @Time : 2025/2/2-1:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3444 动态规划 状态压缩
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = nums.size(), m = target.size(), u = (1 << m) - 1;
        vector<ll> lcms(u + 1, 1);
        for(int s = 1; s <= u; s++) {
            for(int i = 0; i < m; i++) {
                if((1 << i) & s)
                    lcms[s] = lcm(lcms[s], target[i]);
            }
        }
        vector<vector<ll>> dp(n + 1, vector(u + 1, (ll)1e15));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for(int s = 0; s <= u; s++) {
                dp[i][s] = dp[i - 1][s];
                dp[i][s] = min(dp[i][s], cal(lcms[s], num) - num);
                for(int ps = s; ps; ps = (ps - 1) & s)
                    dp[i][s] = min(dp[i][s], dp[i - 1][ps] + cal(lcms[ps ^ s], num) - num);
            }
        }
        return dp[n][u];
    }

    ll cal(ll base, int num) {
        if(base >= num) return base;
        int lo = 1, hi = 1e4;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(mid * base >= num) hi = mid;
            else lo = mid + 1;
        }
        return lo * base;
    }
};