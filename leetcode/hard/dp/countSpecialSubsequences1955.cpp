/**
 * @Time : 2022/12/27-8:04 PM
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
     * dp[i][j] 截止nums[i]以数字j为结尾的所有好序列的数目
     */
    int countSpecialSubsequences(vector<int>& nums) {
        int n = nums.size(), mod = 1e9 + 7;
        vector<vector<long>> dp(n, vector(3, 0l));
        if(nums[0] == 0) dp[0][0] = 1;
        for(int i = 1; i < n; i++){
            for(int j = 0; j < 3; j++)
                dp[i][j] = dp[i - 1][j];
            if(nums[i] == 0) dp[i][0] = (2 * dp[i][0] + 1) % mod;
            if(nums[i] == 1) dp[i][1] = (2 * dp[i][1] + dp[i - 1][0]) % mod;
            if(nums[i] == 2) dp[i][2] = (2 * dp[i][2] + dp[i - 1][1]) % mod;
        }
        return (int)dp[n - 1][2];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}