/**
 * @Time : 2024/5/21-7:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * dp[i][j]:截止i天 获得j时剩余的最多钱数 j <= 5000

  dp[i][j]:
 dp[i - 1][j] + x, 当前不买
 dp[i - 1][j - h[i]] - c[i] + x, 当前要买 要求 dp[i - 1][j - h[i]] >= c[i]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 55;
ll T, m, x, c[N], h[N], sum = 0;

void solve() {
    vector<vector<ll>> dp(m + 1, vector(sum + 1, -1ll));
    dp[0][0] = 0;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= sum; j++) {
            if(dp[i - 1][j] != -1) dp[i][j] = dp[i - 1][j] + x; // 当前不买
            if(j - h[i] >= 0 && dp[i - 1][j - h[i]] >= c[i])
                dp[i][j] = max(dp[i - 1][j - h[i]] - c[i] + x, dp[i][j]);
        }
    }
    for(int i = sum; i >= 0; i--) {
        if(dp[m][i] >= 0) {
            cout << i << "\n";
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> m >> x;
        sum = 0;
        for(int i = 1; i <= m; i++) {
            cin >> c[i] >> h[i];
            sum += h[i];
        }
        solve();
    }
};