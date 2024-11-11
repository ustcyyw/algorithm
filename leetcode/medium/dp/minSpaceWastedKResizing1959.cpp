/**
 * @Time : 2023/3/22-8:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * dp[i][j]: 在区间[0,i]上，改变数组j次的最小浪费值
     */
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        vector<vector<int>> max_val(n, vector(n, 0)), dp(n, vector(k + 1, 0));
        for(int i = 0; i < n; i++){
            for(int j = i, val = 0; j < n; j++){
                val = max(nums[j], val);
                max_val[i][j] = val;
            }
        }
        for(int i = 0; i < n; i++){
            dp[i][0] = (i + 1) * max_val[0][i] - sum[i + 1];
            for(int j = 1; j <= min(k, i - 1); j++){
                dp[i][j] = 1e9;
                // 枚举改变值的点，即在第t个位置改变数组大小，那么在区间[t - 1]上，可以改变j-1次
                // 在t这个位置更改，为了满足要求，就需要将值改为区间[t,i]上的最大值
                for(int t = 1; t <= i; t++){
                    dp[i][j] = min(dp[i][j], dp[t - 1][j - 1] + max_val[t][i] * (i - t + 1) - (sum[i + 1] - sum[t]));
                }
            }
        }
        return dp[n - 1][k];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}