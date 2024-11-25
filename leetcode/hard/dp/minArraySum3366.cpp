/**
 * @Time : 2024/11/24-10:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3366 线性dp
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<vector<int>>> dp(n + 1, vector(op1 + 1, vector(op2 + 1, (int)1e9)));
        dp[0][0][0] = 0;
        int ans = INT_MAX;
        for(int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for(int j = 0; j <= op1; j++) {
                for(int l = 0; l <= op2; l++) {
                    int temp = dp[i - 1][j][l] + num, half = (num + 1) / 2;
                    // 只使用操作1
                    if(j > 0) temp = min(temp, dp[i-1][j-1][l] + half);
                    // 只使用操作2
                    if(l > 0 && num >= k) temp = min(temp, dp[i-1][j][l-1] + num - k);
                    if(j && l) {
                        // 先使用操作1 再使用操作2
                        if(half >= k) temp = min(temp, dp[i-1][j - 1][l-1] + half - k);
                        // 先使用操作2 再使用操作1
                        if(num >= k) temp = min(temp,  dp[i-1][j - 1][l-1] + (num - k + 1) / 2);
                    }
                    dp[i][j][l] = temp;
                    if(i == n) ans = min(ans, dp[i][j][l]);
                }
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}