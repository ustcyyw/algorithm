/**
 * @Time : 2025/10/27-20:28
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3725 1969 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    int countCoprime(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<ll>> dp(n, vector(151, 0ll));
        for(int i = 0; i < m; i++)
            dp[0][mat[0][i]]++;
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int num = mat[i][j];
                for(int p = 1; p <= 150; p++) {
                    int t = gcd(p, num);
                    dp[i][t] = (dp[i][t] + dp[i - 1][p]) % mod;
                }
            }
        }
        return dp[n - 1][1];
    }
};