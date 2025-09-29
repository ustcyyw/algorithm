/**
 * @Time : 2025/9/28-17:37
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3699 2129 动态规划 前缀和优化
 */
 /*
  * dp[i][k][0/1]: 截止第i个位置 以元素k结尾 并且是递增（0）/递减（1）的结尾序列的数目
  * dp[i][k][0]: sum{dp[i-1][j][1], for j in (l, k - 1)}
  * dp[i][k][1]: sum{dp[i-1][j][0], for j in (k + 1, r)}
  * 显然区间求和 前缀和优化
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int d = r - l + 1;
        // 用0来标记升序
        vector<ll> sum0(d + 1, 0), sum1(d + 1, 0), dp0(d, 0), dp1(d, 0);
        for(int i = 1; i <= d; i++)
            sum0[i] = i, sum1[i] = i;
        for(int i = 1; i < n; i++) {
            for(int j = 1; j < d; j++)
                dp0[j] = sum1[j];
            for(int j = 0; j < d - 1; j++)
                dp1[j] = (sum0[d] - sum0[j + 1] + mod) % mod;
            for(int j = 1; j <= d; j++) {
                sum0[j] = (sum0[j - 1] + dp0[j - 1]) % mod;
                sum1[j] = (sum1[j - 1] + dp1[j - 1]) % mod;
            }
        }
        return sum0[d] * 2 % mod;
    }
};