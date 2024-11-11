/**
 * @Time : 2024/6/17-12:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1324E 线性动态规划
 */
/*
  * dp[i][j]:截止i位置已经推迟了j次的最大好值
  * 1. 前面推迟了j-1次 当前也要推迟  dp[i-1][j-1] + (sum - j) % h in [l, r]
  * 2. 前面推荐了j次 当前不退出 dp[i-1][j] + (sum - j) % h in [l, r]
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2005, mod = 998244353;
typedef long long ll;
int T, n, h, l, r, sum[N], dp[N][N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> h >> l >> r;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        sum[i] = sum[i - 1] + num;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            int time = (sum[i] - j) % h, add = time >= l && time <= r;
            dp[i][j] = dp[i - 1][j] + add;
            if(j > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + add);
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i++)
        ans = max(ans, dp[n][i]);
    cout << ans;
};