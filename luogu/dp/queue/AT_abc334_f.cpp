/**
 * @Time : 2023/12/27-9:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * dp[i] 最后送达第i个点并回到起点的最小距离
 * dp[i] = min{dp[j] + dis[j + 1] + dis[i] + sum[j + 1, i], j >= max(0, i - k)}
 *       = min{dp[j] + dis[j + 1] - sum[j + 1], j >= max(0, i - k)} + dis[i] + sum[i]
 * 转移方程 上一个点截止j（dp[j]），那么要从原点出发到j+1这个点（dis[j + 1]），
 * 再走到i这个点（sum[j + 1, i]），最后从i返回原点（dis[i]）
 *
 * 找一个确定区间的最小值 并且这个区间长度确定 单调队列
 * 队列中存放的值，是与j相关的项 dp[j] + dis[j + 1] - sum[j + 1]
 * 边界条件 dp[0] + dis[1] - sum[1] = dis[1]
 *
 * 关于sum[j, i]，表示的是第j个点依次走到第i个点的距离和
 * sum[1] = dis[0][1]
 * sum[2] = dis[0][1] + dis[1][2]
 * sum[3] = dis[0][1] + dis[1][2] + dis[2][3]
 * sum[4] = dis[0][1] + dis[1][2] + dis[2][3] + dis[3][4]
 * 点2到3再到4的距离为 sum[4] - sum[2] = dis[2][3] + dis[3][4]
 * 因此 j + 1这个点到i的距离为sum[i] - sum[j + 1]
 */
#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const int N = 2e5 + 5;
int k, n, sx, sy, x[N], y[N];

ld dis(int x1, int y1, int x2, int y2) {
    long long dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    vector<ld> dp(n + 1, 0), sum(n + 1, 0);
    for(int i = 2; i <= n; i++)
        sum[i] = sum[i - 1] + dis(x[i], y[i], x[i - 1], y[i - 1]);
    deque<pair<int, ld>> queue;
    queue.push_back({0, dis(sx, sy, x[1], y[1])});
    for(int i = 1; i <= n; i++) {
        while(i - queue.front().first > k)
            queue.pop_front();
        dp[i] = queue.front().second + dis(sx, sy, x[i], y[i]) + sum[i];
        if(i != n) {
            ld t = dp[i] + dis(sx, sy, x[i + 1], y[i + 1]) - sum[i + 1];
            while(!queue.empty() && queue.back().second >= t)
                queue.pop_back();
            queue.push_back({i, t});
        }
    }
    printf("%Lf", dp[n]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> sx >> sy;
    for(int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    solve();
}