/**
 * @Time : 2024/5/10-12:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1154F 线性dp + 贪心
 */
 /*
  * 要让总价最便宜 那一定是要买最便宜的k双 然后考虑捆绑购买的情况
  * 因为只能恰好买k双 所以捆绑购买数量超过k的就直接舍弃
  * 对于特定的购买数量x，能免费的鞋子数y越大越好，因此每个x只保留一个y即可
  * 因为k <= min(2000, n), 所以策略数量 <= min(2000, n)
  *
  * dp[i]:截止第i双鞋子的最小支出
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 2005;
int n, m, k, price[N], bd[M], sum[M], dp[M];
vector<vector<int>> arr;

void solve() {
    fill(dp, dp + k + 1, INT_MAX);
    dp[0] = 0;
    for(int i = 1; i <= k; i++) {
        for(auto& b : arr) {
            int x = b[0], y = b[1];
            if(i - x >= 0) dp[i] = min(dp[i], dp[i - x] + sum[i] - sum[i - x + y]);
        }
    }
    cout << dp[k];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        cin >> price[i];
    sort(price, price + n + 1);
    for(int i = 1; i <= k; i++)
        sum[i] = sum[i - 1] + price[i];
    for(int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        if(x > k) continue;
        bd[x] = max(bd[x], y);
    }
    arr.push_back({1, 0}); // 单独购买的情形
    for(int i = 1; i <= k; i++) {
        if(bd[i]) arr.push_back({i, bd[i]});
    }
    solve();
};