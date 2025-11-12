/**
 * @Time : 2024/7/4-11:20 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1409F 动态规划
 */
 /*
  * dp[i][j][k] 截止i位置 已经有j个c1 且已经变换k次的最大数量

1.s[i] == c1
dp[i-1][j-1][k] 当前字符不变 不浪费任何次数
dp[i-1][j][k-1] + j 当前字符变为c2 使用一次变换 那么前一个位置得有j个c1了

2.s[i] == c2
dp[i-1][j][k] + j 当前字符不变 不使用变换操作 前面得有j个c1
dp[i-1][j-1][k-1] 当前字符变为c1

3.不是c1不是c2
dp[i-1][j][k-1] + j 变为c2
dp[i-1][j-1][k-1] 变为c1
不变的情况 dp[i - 1][j][k]

  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, K;
char c1, c2;
string s, t;

void same() {
    ll ans = 0;
    for(int i = 1, sum = 0; i <= n; i++) {
        if(s[i] != c1 && K > 0) s[i] = c1, K--;
        if(s[i] == c2) ans += sum, sum++;
    }
    cout << ans << "\n";
}

void solve() {
    vector<vector<vector<ll>>> dp(n + 1, vector(n + 1, vector(K + 1, LONG_LONG_MIN)));
    ll ans = 0;
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            for(int k = 0; k <= min(K, i); k++) {
                if(j == 0) {
                    dp[i][0][k] = 0;
                    continue;
                }
                if(s[i] == c1) {
                    dp[i][j][k] = dp[i-1][j-1][k];
                    if(k - 1 >= 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + j);
                } else if(s[i] == c2) {
                    dp[i][j][k] = dp[i-1][j][k] + j;
                    if(k - 1 >= 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k-1]);
                } else {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if(k - 1 >= 0)
                        dp[i][j][k] = max({dp[i][j][k],dp[i-1][j][k-1] + j, dp[i-1][j-1][k-1]});
                }
                if(i == n) ans = max(ans, dp[i][j][k]);
            }
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> K >> s >> t;
    c1 = t[0], c2 = t[1];
    s = '.' + s;
    if(c1 == c2) same();
    else solve();
};