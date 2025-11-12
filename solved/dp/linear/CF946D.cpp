/**
 * @Time : 2025/3/23-5:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF946D 1800 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, mod = 1e9 + 7;
int T, n, m, k;
vector<vector<int>> cost, dp;
string s;

void init_cost(int idx) {
    s = '.' + s;
    vector<int> sum(m + 1, 0);
    for(int i = 1; i <= m; i++)
        sum[i] = sum[i - 1] + (s[i] - '0');
    for(int i = 1; i <= m; i++) {
        if(s[i] == '0') continue;
        for(int j = i; j <= m; j++) {
            if(s[j] == '0') continue;
            int c = sum[i - 1] + sum[m] - sum[j];
            cost[idx][c] = min(cost[idx][c], j - i + 1);
        }
    }
    cost[idx][sum[m]] = 0;
}

void solve() {
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            if(j > 0) dp[i][j] = dp[i][j - 1];
            for(int c = 0; c <= min(j, m); c++) {
                if(cost[i][c] == 1e9) continue;
                dp[i][j] = min(dp[i][j], dp[i - 1][j - c] + cost[i][c]);
            }
        }
    }
    cout << dp[n][k] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> k;
        cost = vector(n + 1, vector(m + 1, (int)1e9));
        dp = vector(n + 1, vector(k + 1, (int)1e9));
        for(int i = 1; i <= n; i++) {
            cin >> s;
            init_cost(i);
        }
        solve();
    }
}