/**
 * @Time : 2024/1/24-9:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 首先找到各个子串在哪 pos[i] = true 表示以i为结尾 存在一个子串
 * dp[i][0]: i处不进行修改的最少操作次数
 * dp[i][1]: i处进行修改的最少操作次数
 *
 * pos[i] = true:
 * dp[i][0]: 在[i - len + 1, i - 1]上必须进行一次修改
 * dp[i][1]: 在[i - len + 1, i - 1]上都不能进行修改 由dp[i - len][0], dp[i - len][1]转移
 *
 * pos[i] = false
 * dp[i][0]: dp[i - 1][0], dp[i - 1][1]
 * dp[i][1]: 不可能
 */

#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e9, mod = 1e9 + 7;
int T;
string s, t;

void solve() {
    int n = s.size(), m = t.size();
    vector<bool> pos(n, false);
    for(int i = 0; i + m - 1 < n; i++)
        pos[i + m - 1] = s.substr(i, m) == t;
    vector<vector<int>> dp(n + 1, vector(2, MAX));
    vector<vector<long long>> cnt(n + 1, vector(2, 0ll));
    dp[0][0] = 0, cnt[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        if(pos[i - 1]) {
            for(int j = i - m + 1; j <= i - 1; j++) {
                if(dp[j][1] == dp[i][0]) cnt[i][0] += cnt[j][1];
                if(dp[j][1] < dp[i][0]) dp[i][0] = dp[j][1], cnt[i][0] = cnt[j][1];
            }
            dp[i][1] = min(dp[i - m][0], dp[i - m][1]) + 1;
            if(dp[i][1] == dp[i - m][0] + 1) cnt[i][1] = cnt[i - m][0];
            if(dp[i][1] == dp[i - m][1] + 1) cnt[i][1] += cnt[i - m][1];
        } else {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
            if(dp[i][0] == dp[i - 1][0]) cnt[i][0] = cnt[i - 1][0];
            if(dp[i][0] == dp[i - 1][1]) cnt[i][0] += cnt[i - 1][1];
        }
        cnt[i][0] %= mod, cnt[i][1] %= mod;
    }
    int res = min(dp[n][0], dp[n][1]);
    long long way = (res == dp[n][0] ? cnt[n][0] : 0) + (res == dp[n][1] ? cnt[n][1] : 0);
    cout << res << " " << (way % mod) << endl;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s >> t;

        solve();
    }
}