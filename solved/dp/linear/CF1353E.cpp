/**
 * @Time : 2024/6/26-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1353E 线性动态规划 前缀和
 */
 /*
  * dp[i][0]: 截止i位置灯是灭的操作次数
  * dp[i][1]: 截止i位置灯是开的操作次数
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int T, n, k, sum[N], dp[N][2];
string s;

void solve() {
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + s[i] - '0';
    for(int i = 1; i <= n; i++) {
        int c1 = 0, c0 = 0;
        if(s[i] == '0') c1 = 1;
        else c0 = 1;
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + c0;
        dp[i][1] = sum[i - 1] + c1; // 这是第一个1的情况
        if(i - k >= 1) // 接在前面的1的情况
            dp[i][1] = min(dp[i][1], dp[i - k][1] + sum[i - 1] - sum[i - k] + c1);
    }
    cout << min(dp[n][0], dp[n][1]) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> s;
        s = '.' + s;
        solve();
    }
};