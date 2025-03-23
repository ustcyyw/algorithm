/**
 * @Time : 2025/3/21-5:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1467D 2200 动态规划 贡献法 (看了题解)
 */
/*
  * dp[i][j]: 走到i点 用了j步的可能走法数目
  * f[i][j]: 从i点出发 再走j步的走法数目
  * 走到i点 用了j步 描述的是以i为终点 路径长度j的可能路径数
  * 那么路径倒转 就相当于以i为起点 再走长度j 所以f[i][j] = dp[i][j]
  *
  * 走j步到达i点，后面还能再走k-j步，所有可能的路径是 dp[i][j] * f[i][k - j]
  * cnt[i] = sum{dp[i][j] * f[i][k - j]}
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5005 + 15, mod = 1e9 + 7;
int T, n, k, q, nums[N];
ll dp[N][N], cnt[N];

void init() {
    for(int i = 1; i <= n; i++) {
        dp[i][0] = 1; // 走到i 走了0步 也就是以i为起点
    }
    for(int j = 1; j <= k; j++) {
        for(int i = 1; i <= n; i++)
            dp[i][j] = (dp[i - 1][j - 1] + dp[i + 1][j - 1]) % mod;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++)
            cnt[i] = (cnt[i] + dp[i][j] * dp[i][k - j] % mod) % mod;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> q;
    init();
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        sum = (sum + nums[i] * cnt[i] % mod) % mod;
    }
    for(int i = 1, idx, v; i <= q; i++) {
        cin >> idx >> v;
        ll diff = v - nums[idx], temp = diff * cnt[idx] % mod;
        sum = ((sum + temp) % mod + mod) % mod;
        nums[idx] = v;
        cout << sum << "\n";
    }
}