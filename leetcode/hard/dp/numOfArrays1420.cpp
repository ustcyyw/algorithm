/**
 * @Time : 2022/12/30-11:06 AM
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
     * cost = 顺序扫描过程中遇到更大的数的次数 + 1
     *
     * dp[i][j][c]: 截止数组索引i，以j这个数字为子数组最大值，且cost为c的方案数
     * 转移方程：
     * 1.如果当前位选择了小于等于j的数（共有j个），那么前置位出现过最大值j
     * 截止当前位最大值还是j，并且不会增加cost： dp[i][j][c] += dp[i - 1][j][c] * j
     * 2.如果当前位选择了j，那么前置位出现过的最大数从l 从1到j-1，截止当前位最大值变j
     * 并且cost要+1， dp[i][j][c] += sum{dp[i - 1][l][c - 1]} for 1 <= l < j
     * 以上两种情况求和
     *
     * 因为cost = 顺序扫描过程中遇到更大的数的次数 + 1
     * 数组第一个数一定会消耗1，忽略这个必然的1，计算的时候只要计算到 cost = 顺序扫描过程中遇到更大的数的次数即可。
     * 因而状态计算只需要计算到k-1
     * 初始状态 dp[0][j][0] = 1，表示不论第一个数选择什么，cost都为0，方案数为1
     *
     * 截止dp[i][j][c]
     * 后面还有n - i - 1位，还需要消耗 k - 1 - c，还可以更大的数有m-j个
     * 因此 k - 1 - c <= min(n - i - 1, m - j)
     * c >= k - 1 - min(n - i - 1, m - j)
     * 因此c的枚举从 max(1, k - 1 - min(n - i - 1, m - j))开始
     *
     * 前面有i位，已用j个数，最多能消耗 min(i, j)，因此c <= min(i, j)
     *
     */
    int mod = 1e9 + 7;
    int numOfArrays(int n, int m, int k) {
        vector<vector<vector<long>>> dp(n, vector(m + 1, vector(k, 0l)));
        for(int j = 1; j <= m; j++)
            dp[0][j][0] = 1;
        for(int i = 1; i < n; i++){
            for(int j = 1; j <= m; j++){
                dp[i][j][0] = (dp[i - 1][j][0] * j) % mod;
                for(int c = max(1, k - 1 - min(n - i - 1, m - j)); c < k && c <= min(i, j); c++){
                    // 当前的数字选则小于等于j的 那么截止前一位最大数字是j的，到当前位不会增加cost
                    dp[i][j][c] = (dp[i - 1][j][c] * j) % mod;
                    // 当前数字选j，前面数字小于j，会增加1的cost
                    for(int l = 1; l < j; l++){ // 枚举前面的数字小于j的情况
                        dp[i][j][c] = (dp[i][j][c] + dp[i - 1][l][c - 1]) % mod;
                    }
                }
            }
        }
        long res = 0;
        for(int j = 1; j <= m; j++)
            res = (res + dp[n - 1][j][k - 1]) % mod;
        return (int)res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}