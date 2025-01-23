/**
 * @Time : 2025/1/22-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF9D 1900 动态规划
 */
 /*
  * dp[i][j]: 有i个结点 高度<=j的方案数
  * 左右子结点之和为i-1
  * dp[left][j-1] * dp[right][j-1]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2505, mod = 998244353;
ll T, n, h, dp[36][36];

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> h;
        for(int i = 0; i <= n; i++)
            dp[0][i] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                for(int c1 = 0; c1 <= i - 1; c1++)
                    dp[i][j] += dp[c1][j - 1] * dp[i - 1 - c1][j - 1];
            }
        }
        cout << dp[n][n] - dp[n][h - 1];
    }
};