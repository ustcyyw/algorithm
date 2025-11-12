/**
 * @Time : 2024/4/2-4:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 对于每一行 用队列优化dp来计算
  * k行的计算 滑动窗口
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, m, k, d, grid[101][N], val[101];

ll cal(ll* line) {
    vector<ll> dp(m + 1, 0);
    deque<pair<int, ll>> dq;
    dp[1] = line[1] + 1, dq.push_back({1, dp[1]});
    for(int i = 2; i <= m; i++) {
        while(!dq.empty() && i - dq.front().first - 1 > d) dq.pop_front();
        dp[i] = line[i] + 1 + dq.front().second;
        while(!dq.empty() && dq.back().second >= dp[i]) dq.pop_back();
        dq.push_back({i, dp[i]});
    }
    return dp[m];
}

void solve() {
    ll ans = LONG_LONG_MAX, sum = 0;
    for(int i = 1, j = 1; j <= n; j++) {
        val[j] = cal(grid[j]);
        sum += val[j];
        if(j - i + 1 > k) sum -= val[i++];
        if(j - i + 1 == k) ans = min(ans, sum);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k >> d;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++)
                cin >> grid[i][j];
        }
        solve();
    }
};