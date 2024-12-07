/**
 * @Time : 2024/12/6-11:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2050E 1537 动态规划 线性dp
 */
/*
 * dp[i][j]: 截止i位置匹配a到j位置的最小修改次数 j <= i
 * 那么匹配给b的自负一共有 i - j 个, i - j <= lenB
 * 1. s[i]匹配给a
 *    1.1 s[i] = a[j], dp[i][j] = dp[i-1][j-1]
 *    1.2 s[i] != a[j], dp[i][j] = dp[i-1][j-1] + 1
 * 2. s[i]匹配给b
 *    2.1 s[i] = b[i-j], dp[i][j] = dp[i-1][j]
 *    2.2 s[i] != b[i-j], dp[i][j] = dp[i-1][j] + 1
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T;
string a, b, s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> a >> b >> s;
        int na = a.size(), nb = b.size(), n = na + nb;
        a = '.' + a, b = '.' + b, s = '.' + s;
        vector<vector<int>> dp(n + 1, vector(na + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = max(0, i - nb); j <= min(i, na); j++) {
                int c1 = s[i] != a[j], c2 = s[i] != b[i-j];
                int t1 = j > 0 ? dp[i-1][j-1] + c1 : INT_MAX;
                int t2 = j < i ? dp[i-1][j] + c2 : INT_MAX;
                dp[i][j] = min(t1, t2);
            }
        }
        cout << dp[n][na] << "\n";
    };
};