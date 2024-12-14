/**
 * @Time : 2024/12/13-11:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3320 2153 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
unordered_map<char, int> mp = {{'F',0}, {'W',1},{'E',2}};
unordered_map<int, int> point = {{2,-1},{10,-1},{21,-1},
                                 {20,1},{1,1},{12,1},
                                 {0,0},{11,0},{22,0}};

class Solution {
public:
    int countWinningSequences(string s) {
        int n = s.size();
        vector<vector<vector<ll>>> dp(n, vector(2 * n + 1, vector(3, 0ll)));
        for(int i = 0; i < n; i++)
            dp[0][getP(s[0], i) + n][i] = 1;
        for(int i = 1; i < n; i++) {
            for(int j = n - i - 1; j <= n + i + 1; j++) {
                for(int k = 0; k < 3; k++) {
                    int d = getP(s[i], k), pre = j - d;
                    if(pre < n - i || pre > n + i) continue;
                    for(int pk = 0; pk < 3; pk++) {
                        if(pk == k) continue;
                        dp[i][j][k] = (dp[i][j][k] + dp[i - 1][pre][pk]) % mod;
                    }
                }
            }
        }
        ll ans = 0;
        for(int j = n + 1; j <= 2 * n; j++) {
            for(int k = 0; k < 3; k++)
                ans = (ans + dp[n - 1][j][k]) % mod;
        }
        return ans;
    }

    int getP(char ca, int cb) {
        int key = mp[ca] * 10 + cb;
        return point[key];
    }
};