/**
 * @Time : 2024/5/22-9:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1249E 动态规划 线性dp
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, c, a[N], b[N], dp[N][2];

void solve() {
    dp[0][0] = 0, dp[0][1] = c;
    for(int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
        dp[i][1] = min(dp[i - 1][0] + c, dp[i - 1][1]) + b[i];
    }
    for(int i = 0; i < n; i++)
        cout << min(dp[i][0], dp[i][1]) << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> c;
    for(int i = 1; i < n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++)
        cin >> b[i];
    solve();
};