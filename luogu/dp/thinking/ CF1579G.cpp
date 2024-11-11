/**
 * @Time : 2024/7/13-5:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1579G 动态规划 状态定义和转移方程困难
 */
/*
 * 容易发现 最大的可能长度是 2 * maxLen, (maxLen = max{ai})
 * 假设线段的范围就是[-maxLen, maxLen]
 * 那么只要终点坐标大于0 就让他往左边放 终点坐标<=0 就让他往右放
 * 由于线段长度都 <= maxLen， 因此不会超出边界
 *
 * 定义 dp[i][j]: 第i个线段放置结束时 终点x 距离左边界l距离为j时 离右边界r的最短距离
 * 定义忽略了具体l和r的值 只关注x与l距离为某个定值j时 离r的最短距离
 * (就和高度差值 高低相关的排列方式等一样 绝对的位置 绝对的高度无意义 都是计算相对值)
 * 于是答案就是 min(dp[n][j] + j)
 *
 * 初状态所有 dp[i][j] = MAX_VAL 表示第i个线段到左边界的距离为j的情况不存在（要由前置状态来确定）
 * dp[0][0] = 0: 不放任何线段时 左右边界同一个点 距离左边界的距离只能时0，同时离右边界也是0
 *
 * 转移方程 当前dp[i][j]已知道 考虑下一个线段如何放置
 * 1. 向左放
 * 如果 j - a[i + 1] < 0, 说明左边界要更新了
 * dp[i + 1][0] = min(dp[i + 1][0], dp[i][j] + a[i + 1])
 * 如果 j - a[i + 1] >= 0, 左边界不变，终点距离左边界的的值为j - a[i + 1]
 * dp[i + 1][j - a[i + 1]] = min(dp[i + 1][j - a[i + 1]], dp[i][j] + a[i + 1])
 * 统一写为 dp[i + 1][t] = min(dp[i + 1][t], dp[i][j] + a[i + 1])
 * 其中 t = max(0, j - a[i + 1])
 * 2. 向右放
 * 如果 j + a[i + 1] > m 跳出规定的有边界 没意义 不进行计算
 * 否则 j + a[i + 1] <= m
 * dp[i + 1][j + a[i + 1]] = min(dp[i + 1][j + a[i + 1]], max(dp[i][j] - a[i + 1], 0))
 * 注意max(dp[i][j] - a[i + 1], 0)的含义，到右边界的距离不能为负
 * 为负时说明这个线段终点成了新的右边界，终点和右边界的距离显然为0
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, a[N];

void solve() {
    m = 2 * m;
    vector<vector<int>> dp(n + 1, vector(m + 1, INT_MAX));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0, len = a[i + 1]; j <= m; j++) {
            if(dp[i][j] == INT_MAX) continue;
            int t = max(0, j - len);
            dp[i + 1][t] = min(dp[i + 1][t], dp[i][j] + len);
            if(j + len <= m)
                dp[i + 1][j + len] = min(dp[i + 1][j + len], max(dp[i][j] - len, 0));
        }
    }
    int ans = INT_MAX;
    for(int j = 0; j <= m; j++)
        if(dp[n][j] != INT_MAX) ans = min(ans, dp[n][j] + j);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        m = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            m = max(m, a[i]);
        }
        solve();
    }
};