/**
 * @Time : 2023/12/14-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 3005, mod = 998244353;

int n, a[N], b[N];

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
    // dp[i][j] 第i位取数字 <= j - 1的方案数
    vector<vector<long long>> dp(n, vector(N + 1, 0ll));
    for(int i = a[0]; i < N; i++)
        dp[0][i + 1] = dp[0][i] + (i <= b[0]);
    for(int i = 1; i < n; i++) {
        for(int j = a[i]; j < N; j++) {
            dp[i][j + 1] = (dp[i][j] + (j <= b[i] ? dp[i - 1][j + 1] : 0)) % mod;
        }
    }
    cout << dp[n - 1][b[n - 1] + 1] << endl;
}