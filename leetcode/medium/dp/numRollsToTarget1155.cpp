/**
 * @Time : 2023/2/22-6:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>> dp(n + 1, vector(target + 1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            for(int sum = i; sum <= min(k * i, target); sum++){
                for(int j = 1; j <= k && sum - j >= 0; j++)
                    dp[i][sum] = (dp[i][sum] + dp[i - 1][sum - j]) % mod;
            }
        }
        return dp[n][target];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}