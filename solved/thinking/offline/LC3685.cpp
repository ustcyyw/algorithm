/**
 * @Time : 2025/9/30-10:53
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3685 2081 离线思维 背包dp
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<bool> ans, dp(k + 1, false);
        dp[0] = true;
        for(int x = 1, i = 0, sum = 0; x <= n; x++) {
            while(i < n && nums[i] < x) {
                sum += nums[i];
                vector<bool> temp(k + 1, false);
                temp[0] = true;
                for(int j = 1; j <= min(k, sum); j++)
                    temp[j] = dp[j] || (j - nums[i] >= 0 && dp[j - nums[i]]);
                swap(temp, dp);
                i++;
            }
            ans.push_back(check(dp, k, x, n - i));
        }
        return ans;
    }

    bool check(vector<bool>& dp, int k, int x, int cnt) {
        for(int j = 0; j <= k; j++) {
            if(!dp[j]) continue;
            int left = k - j;
            if(left % x == 0 && left / x <= cnt) return true;
        }
        return false;
    }
};