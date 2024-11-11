/**
 * @Time : 2024/5/29-8:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1829H 状压dp
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, u = 63;
ll dp[N][64];

void solve() {
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        for(int j = 0; j <= u; j++) {
            dp[i][j] = dp[i - 1][j];
            for(int p = 0; p <= u; p++) {
                if((p & num) == j)
                    dp[i][j] = (dp[i][j] + dp[i - 1][p]) % mod;
            }
        }
    }
    ll ans = 0;
    for(int j = 0; j <= u; j++) {
        if(__builtin_popcount(j) == k)
            ans += dp[n][j];
    }
    if(k == 6) ans = ans - 1 + mod; // 把非空的那一个去掉
    cout << ans % mod << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    dp[0][63] = 1;
    while(T-- > 0) {
        cin >> n >> k;
        solve();
    }
};