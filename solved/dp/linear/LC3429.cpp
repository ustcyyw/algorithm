/**
 * @Time : 2025/1/19-3:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3429 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    long long minCost(int n, vector<vector<int>>& cost) {
        int m = n / 2 - 1;
        vector<vector<vector<ll>>> dp(m + 1, vector(3, vector(3, LONG_LONG_MAX)));
        ll ans = LONG_LONG_MAX;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j) continue;
                dp[0][i][j] = cost[0][i] + cost[n - 1][j];
                if(m == 0) ans = min(ans, dp[0][i][j]);
            }
        }
        for(int i = 1; i <= m; i++) {
            for(int j1 = 0; j1 < 3; j1++) {
                for(int j2 = 0; j2 < 3; j2++) {
                    if(j1 == j2) continue;
                    ll c = cost[i][j1] + cost[n - 1 - i][j2];
                    for(int j3 = 0; j3 < 3; j3++) {
                        if(j3 == j1) continue;
                        for(int j4 = 0; j4 < 3; j4++) {
                            if(j4 == j2 || dp[i - 1][j3][j4] == LONG_LONG_MAX) continue;
                            dp[i][j1][j2] = min(dp[i][j1][j2], dp[i - 1][j3][j4] + c);
                        }
                    }
                    if(i == m) ans = min(ans, dp[i][j1][j2]);
                }
            }
        }
        return ans;
    }
};