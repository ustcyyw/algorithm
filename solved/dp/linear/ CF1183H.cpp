/**
 * @Time : 2024/5/22-11:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1183H dp + 贪心
 */
/*
 * dp[i][j]: 以i结尾的 且长度为j的不同子序列数量
 * sum[i][j]: 截止i-1 不同字符为结尾的且长度为j的不同子序列数量和
 * 并且数量超过k就没意义了
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, k, dp[105][105], last[30];
string s;

void solve() {
    fill(last, last + 26, -1);
    for(int i = 1; i <= n; i++) {
        dp[i][1] = 1;
        for(int c = 0; c < 26; c++) {
            if(last[c] == -1) continue;
            for(int j = 2; j <= i; j++) {
                dp[i][j] += dp[last[c]][j - 1];
            }
        }
        last[s[i] - 'a'] = i;
    }
    ll ans = 0;
    for(int m = n; m > 0 && k > 0; m--) {
        for(int c = 0; c < 26 && k > 0; c++) {
            if(last[c] == -1) continue;
            ll t = min(k, dp[last[c]][m]);
            ans += (n - m) * t;
            k -= t;
        }
    }
    if(k > 0) ans += n, k--;
    cout << (k > 0 ? - 1 : ans);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    cin >> s;
    s = '.' + s;
    solve();
};