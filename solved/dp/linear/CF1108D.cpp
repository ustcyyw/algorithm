/**
 * @Time : 2024/4/29-3:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1108D 线性动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int n, dp[N][3], info[N][3];
char change[3] = {'R', 'G', 'B'};
string s;

void solve() {
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            dp[i][j] = 1e9;
            for(int k = 0; k < 3; k++) {
                if(k != j && dp[i - 1][k] < dp[i][j]) {
                    dp[i][j] = dp[i - 1][k];
                    info[i][j] = k;
                }
            }
            dp[i][j] += change[j] == s[i] ? 0 : 1;
        }
    }
    int color = 0, ans = dp[n][0];
    for(int i = 1; i < 3; i++) {
        if(dp[n][i] < ans)
            ans = dp[n][i], color = i;
    }
    cout << ans << "\n";
    for(int i = n; i > 0; i--) {
        s[i] = change[color];
        color = info[i][color];
    }
    cout << s.substr(1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    s = '.' + s;
    solve();
};