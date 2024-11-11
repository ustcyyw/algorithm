/**
 * @Time : 2024/7/4-8:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1426F 动态规划
 */
/*
 * dp[i][0]: a的序列数目
 * dp[i][1]: ab的序列数目
 * dp[i][2]: abc的序列数目
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, dp[N][3] = {0};
string s;

void solve() {
    ll cnt = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++)
            dp[i][j] = dp[i - 1][j];
        if(s[i] == 'a') dp[i][0] = (dp[i][0] + cnt) % mod; // 因为?的缘故有cnt个字符串 那么a的序列得+cnt
        else if(s[i] == 'b') dp[i][1] = (dp[i][1] + dp[i - 1][0]) % mod;
        else if(s[i] == 'c') dp[i][2] = (dp[i][2] + dp[i - 1][1]) % mod;
        else { // 系数3表示 当前字母可以换成abc中任意一个 对于每个字母 前面得到的序列都需要累加
            dp[i][0] = (3 * dp[i][0] % mod + cnt) % mod;
            dp[i][1] = (3 * dp[i][1] % mod + dp[i - 1][0]) % mod;
            dp[i][2] = (3 * dp[i][2] % mod + dp[i - 1][1]) % mod;
            cnt = cnt * 3 % mod;
        }
    }
    cout << dp[n][2];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    s = '.' + s;
    solve();
};