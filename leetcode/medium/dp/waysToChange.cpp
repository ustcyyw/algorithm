/**
 * @Time : 2022/6/13-2:03 AM
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
     * dp[j][i] : 以硬币j为最后一个硬币，能凑成i面值的方法数量
     * sum[j][i] : 以硬币0，1，2...j为结尾，面值i的方法数量之和
     */
    int coins[4] = {1, 5, 10, 25};
    int mod = 1000000007;
    int waysToChange(int n) {
        vector<vector<long>> dp = vector(4, vector(n + 1, 0l));
        vector<vector<long>> sum = vector(4, vector(n + 1, 0l));
        for(int i = 0; i < 4; i++) sum[i][0] = 1;
        for(int i = 1; i <= n; i++){
            dp[0][i] = 1;
            sum[0][i] = 1;
            for(int j = 1; j <= 3 && i - coins[j] >= 0; j++)
                dp[j][i] = (dp[j][i] + sum[j][i - coins[j]]) % mod;
            for(int j = 1; j <= 3; j++)
                sum[j][i] = (sum[j - 1][i] + dp[j][i]) % mod;
        }
        return (int) sum[3][n] % mod;
    }
};

int main(){
    Solution s;
    cout << s.waysToChange(5) << endl;
}