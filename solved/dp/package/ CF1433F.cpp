/**
 * @Time : 2024/7/6-1:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1433F 动态规划 01背包
 */
/*
  * dp[i][j][k]: 截止第i个元素 拿了j个 余数为k的最大和

dp[i][j][k]:
1. 不取的情况 dp[i - 1][j][k]
2. 取当前数字的情况 dp[i-1][j-1][pre] + num

t = num % mod, (pre + t) % mod = k

t <= k, pre = k - t
t > k, pre = (k - t + mod) % mod

  每一行开始的dp[0]都是上一行的dp[m]转移而来
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 72, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, K, grid[N][N];

void solve() {
    int half = m / 2;
    vector<vector<vector<int>>> dp(m + 1, vector(half + 1, vector(K, -(int)1e9)));
    dp[0][0][0] = 0;
    for(int l = 1; l <= n; l++) {
        for(int i = 1; i <= m; i++) {
            dp[i][0][0] = dp[i - 1][0][0];
            int num = grid[l][i], t = num % K;
            for(int j = 0; j <= min(i, half); j++) {
                for(int k = 0; k < K; k++) {
                    int pre = (k - t + K) % K;
                    dp[i][j][k] = dp[i - 1][j][k];
                    if(j - 1 >= 0) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][pre] + num);
                }
            }
        }
        for(int k = 0; k < K; k++) {
            for(int j = 0; j <= half; j++)
                dp[0][0][k] = max(dp[m][j][k], dp[0][0][k]);
        }
    }
    int ans = 0;
    for(int j = 0; j <= half; j++)
        ans = max(dp[m][j][0], ans);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> K;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cin >> grid[i][j];
    }
    solve();
};