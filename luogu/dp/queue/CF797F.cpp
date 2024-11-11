/**
 * @Time : 2024/6/29-11:23 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF797F 动态规划 单调队列优化
 */
 /*
  * dp[i][j]：i个洞处理前j个球的最小距离

dp[i-1][j - 1] + dis(a[j], p[i])
dp[i-1][j - 2] + dis(a[j], p[i]) + dis(a[j - 1], p[i])
dp[i-1][j - 3] + dis(a[j], p[i]) + dis(a[j - 1], p[i]) + dis(a[j - 2], p[i])

dp[i-1][j - k] + sum(dis(a[j - k + 1], p[i]))
= dp[i-1][j - k] - sum[j - k] + sum[j]
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 5000 + 5;
typedef long long ll;
ll T, n, m, x[N], c_sum[N], preSum[N];
vector<vector<ll>> infos;

ll solve() {
    c_sum[0] = infos[0][1];
    for(int i = 1; i < m; i++)
        c_sum[i] = c_sum[i - 1] + infos[i][1];
    if(c_sum[m - 1] < n) return -1;
    vector<vector<ll>> dp(m, vector(n + 1, (ll)1e18));
    for(int i = 0; i < m; i++) {
        deque<int> dq; // 存放最小值的下标
        dp[i][0] = 0; //截止当前洞都不放任何东西
        dq.push_back(0); //截止前一个洞什么都不放任何一个东西
        for(int j = 1; j <= min(n, c_sum[i]); j++) {
            preSum[j] = preSum[j - 1] + abs(infos[i][0] - x[j]);
            if(i == 0) {
                dp[i][j] = preSum[j];
                continue;
            }
            ll temp = dp[i - 1][j] - preSum[j];
            while(!dq.empty() && dp[i - 1][dq.back()] - preSum[dq.back()] >= temp)
                dq.pop_back();
            dq.push_back(j);
            while(!dq.empty() && j - dq.front() > infos[i][1])
                dq.pop_front();
            dp[i][j] = dp[i - 1][dq.front()] - preSum[dq.front()] + preSum[j];
        }
    }
    return dp[m - 1][n];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    sort(x + 1, x + n + 1);
    for (int i = 1, p, c; i <= m; i++) {
        cin >> p >> c;
        infos.push_back({p, c});
    }
    sort(infos.begin(), infos.end());
    cout << solve();
};