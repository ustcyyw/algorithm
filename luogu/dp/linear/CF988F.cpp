/**
 * @Time : 2024/4/11-12:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * dp[i][j]:走到i位置 并且拿着第j把伞的最小代价
  * 特殊地 j = 0 代表没有拿伞
  * cost[i] = min{dp[i][j]}，到达i位置的最小代价
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2005, T = 1e9;
int a, n, m, diff[N] = {0}, rain[N], cost[N];
vector<vector<int>> w;

void solve() {
    sort(w.begin(), w.end());
    fill(cost, cost + a + 1, T);
    vector<vector<int>> dp(a + 1, vector(m + 1, T));
    cost[0] = 0; // 起点的代价是0
    for(int i = 1; i <= a; i++) {
        // 因为是拿着第j把伞走到i位置，所以第j把伞的位置w[j][0]要小于i
        for(int j = 1; j <= m && w[j][0] < i; j++) {
            int x = w[j][0], p = w[j][1];
            // 从x位置拿起j把伞 走到当前位置 前面怎么拿伞无所谓 所以是用cost[x]进行转移
            dp[i][j] = cost[x] + p * (i - x);
            cost[i] = min(cost[i], dp[i][j]); // 更新到i位置的
        }
        // 特殊处理不拿伞的情况 从x不拿伞走过来 得保证x及其右边都没雨 因此从i-1开始枚举 直到第一个下雨点
        for(int x = i - 1; x >= 0 && rain[x] == 0; x--)
            dp[i][0] = min(dp[i][0], cost[x]);
        cost[i] = min(cost[i], dp[i][0]);
    }
    cout << (cost[a] >= T ? -1 : cost[a]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> n >> m;
    for(int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        // 注意对下雨的定义 从x走到x+1需要用伞 得满足 x >= l, x + 1 <= r。
        // 因此设定r这个点并不是下雨 下雨的点是[l, r - 1]
        diff[l]++, diff[r]--;
    }
    for(int i = 0, t = 0; i <= a; i++) {
        t += diff[i];
        rain[i] = t;
    }
    w.push_back({0, 0});
    for(int i = 1, x, p; i <= m; i++) {
        cin >> x >> p;
        w.push_back({x, p});
    }
    solve();
};