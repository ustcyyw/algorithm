/**
 * @Time : 2024/4/11-11:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * dp[i][0] : 截止i位置 两个条件都不满足
  * dp[i][1] : 截止i位置只满足 s[i] < t[i]
  * dp[i][2] : 截止i位置只满足 s[i] > t[i]
  * dp[i][3] : 截止i位置 两个条件都满足
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll n, dp[N][4] = {0};
string s, t;

void solve() {
    dp[0][0] = 1;
    int c0, c11, c12, c21, c22, c31, c32, c33;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '?' && t[i] == '?') {
            c0 = 10, c32 = c11 = 45, c12 = 55, c31 = c21 = 45, c22 = 55, c33 = 100;
        } else if (s[i] == '?') { // t[i]是具体的数字
            int num = t[i] - '0';
            c0 = 1, c32 = c11 = num, c12 = num + 1, c31 = c21 = 9 - num, c22 = 10 - num, c33 = 10;
        } else if(t[i] == '?') {
            int num = s[i] - '0';
            c0 = 1, c32 = c11 = 9 - num, c12 = 10 - num, c31 = c21 = num, c22 = num + 1, c33 = 10;
        } else { // 数字都固定的情况
            bool f0 = s[i] == t[i], f1 = s[i] < t[i], f2 = s[i] > t[i];
            c0 = f0, c32 = c11 = f1, c12 = f1 + f0, c31 = c21 = f2, c22 = f2 + f0, c33 = 1;
        }
        dp[i][0] = c0 * dp[i - 1][0];
        dp[i][1] = (c11 * dp[i - 1][0] + c12 * dp[i - 1][1]) % mod;
        dp[i][2] = (c21 * dp[i - 1][0] + c22 * dp[i - 1][2]) % mod;
        dp[i][3] = (c31 * dp[i - 1][1] + c32 * dp[i - 1][2] + c33 * dp[i - 1][3]) % mod;
    }
    cout << dp[n][3];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s >> t;
    s = '.' + s, t = '.' + t;
    solve();
};