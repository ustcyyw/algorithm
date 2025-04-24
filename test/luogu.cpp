/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, mod = 998244353;
int T, n, k;
ll g[505], dp[N][N][2]; // g[i]: 表示连续颜色的长度 <= i的可能方案数

ll cal(int limit) {
    dp[0][1][0] = dp[0][1][1] = 1;
    ll sum0 = 1, sum1 = 1;
    for(int i = 1; i < n; i++) {
        dp[i][1][0] = sum1, dp[i][1][1] = sum0;
        for(int j = 2; j <= min(limit, i + 1); j++) {
            dp[i][j][0] = dp[i-1][j-1][0], sum0 = (sum0 + dp[i][j][0]) % mod;
            dp[i][j][1] = dp[i-1][j-1][1], sum1 = (sum1 + dp[i][j][1]) % mod;
        }
    }
    return (sum0 + sum1) % mod;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for(int len = 1; len <= n; len++)
        g[len] = cal(len);
    ll ans = 0;
    for(int a = 1; a < k; a++) {
        ll cnt1 = (g[a] - g[a - 1] + mod) % mod;
        for(int b = 1; a * b < k; b++) {
            ll cnt2 = (g[b] - g[b - 1] + mod) % mod;
            ans = (cnt1 * cnt2 % mod + ans) % mod;
        }
    }
    cout << ans << "\n";
}