/**
 * @Time : 2023/11/30-10:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>

using namespace std;
const int mod = 1e9 + 7;
int n, m, K;
string a, b;

int main() {
    cin >> n >> m >> K;
    cin >> a >> b;
    a = " " + a, b = " " + b;
    // 预处理公共后缀
    vector<vector<int>> suf(n + 1, vector(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) suf[i][j] = suf[i - 1][j - 1] + 1;
        }
    }
    // dp[i][j][k]: 使用s[0,i]上的子串能连接出t[0,j]的 并且刚好使用k个子串的方案数
//    for (int k = 1; k <= K; k++) {
//        for (int i = 1; i <= n; i++) {
//            for (int j = 1; j <= m; j++) {
//                dp[i][j][k] = dp[i - 1][j][k];
//                for (int l = 1; l <= suf[i][j]; l++)
//                    dp[i][j][k] = (dp[i][j][k] + dp[i - l][j - l][k - 1]) % mod;
//            }
//        }
//    }
    // 前缀和优化 滚动数组优化
    vector<vector<long long>> dp(n + 1, vector(m + 1, 0ll));
    vector<vector<long long>> sum(n + 2, vector(m + 2, 0ll));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        for(int j = 0; j <= m; j++)
            sum[i+1][j+1] = dp[i][j] + sum[i][j];
    }
    for (int k = 1; k <= K; k++) {
        vector<vector<long long>> dp2(n + 1, vector(m + 1, 0ll));
        vector<vector<long long>> sum2(n + 2, vector(m + 2, 0ll));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int li = i - suf[i][j], ri = i - 1, lj = j - suf[i][j], rj = j - 1;
                dp2[i][j] = (dp2[i - 1][j] + sum[ri + 1][rj + 1] - sum[li][lj] + mod) % mod;
                sum2[i+1][j+1] = (dp2[i][j] + sum2[i][j]) % mod;
            }
        }
        swap(dp, dp2), swap(sum, sum2);
    }
    cout << dp[n][m] << endl;
    return 0;
}