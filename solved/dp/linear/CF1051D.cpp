/**
 * @Time : 2025/4/29-11:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1051D 1700 动态规划
 */
 /*
  * 0:都是白
  * 1:上白下黑
  * 2:上黑下白
  * 3.全黑
  *
  * dp[i][j][s]: 截止i位置 有j个连通分量 并且以状态s结尾的方案数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3+ 5, mod = 998244353;
ll T, n, k, dp[N][2 * N][4];
int val[4][4] = {{0, 0, 0, 1}, {1, 0, 2, 1},
                 {1, 2, 0, 1},{1, 0, 0, 0}};

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    dp[1][1][0] = 1, dp[1][2][1] = 1, dp[1][2][2] = 1, dp[1][1][3] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= min(2 * n, k); j++) {
            for(int s = 0; s < 4; s++) {
                for(int p = 0; p < 4; p++) {
                    int v = val[s][p];
                    if(j - v >= 0) dp[i][j][s] = (dp[i][j][s] + dp[i - 1][j - v][p]) % mod;
                }
            }
        }
    }
    ll ans = 0;
    for(int s = 0; s < 4; s++)
        ans += dp[n][k][s];
    cout << ans % mod;
}