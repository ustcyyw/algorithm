/**
 * @Time : 2025/1/31-11:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3290 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 5e4 + 5, P = 13331;

class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<vector<ll>> dp(n + 1, vector(5, (ll)-1e12));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            dp[i][0] = 0;
            ll nums1 = b[i - 1];
            for(int j = 1; j <= 4; j++)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[j - 1] * nums1);
        }
        return dp[n][4];
    }
};
