/**
 * @Time : 2024/6/26-9:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1353F 动态规划 + 暴力枚举
 */
/*
  * 第一个点的高度假如是h 那么在(i,j)点的高度为 h[i,j] = h + i + j - 2
  * 如果grid[i][j] >= h[i,j], cost = grid[i][j] - h[i,j]
  * 但问题的关键是 h如何确定
  * 结论：最终答案所选的走法中 必定有一个点没有改动过高度
  * 可以使用反证法：假设最终答案所选的走法中 每个点高度都降低了
  * 首先明确 最终答案的走法已经是操作次数最少的了，而这个走法中每个点高度都至少下降1
  * 那么我们让每个点高度再提高1，就等价于少用了 m + n - 1 次降低高度的操作 于是总操作次数更少了。
  * 如果此时每个点高度还是比一开始有下降，那继续每个点高度再提高1 总操作数更少
  * ... 直到有一个点已经和初始高度相同了，此时不可能再将路径中每个点高度+1了
  * 而此时总操作数 < 每个点都改动过高度的同一条路径的总操作数
  * 和假设矛盾 因此最终答案所选的路径 一定存在至少一个点高度没有变化
  *
  * 那么就可以枚举没有改动过高度的点，倒推出初始高度h，计算指定h下的最小总操作数
  * 将这些所有可能的答案中选最小即可
  * （当然有些初始高度会导致根本没法走到终点，但是无所谓 会枚举到最终答案路径经过的那个不改变高度的点）
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 105;
typedef long long ll;
int T, n, m;
ll grid[N][N], LM = LONG_LONG_MAX;

ll cal(ll h) {
    vector<vector<ll>> dp(n + 1, vector(m + 1, LM));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ll ch = h + i + j - 2;
            if(grid[i][j] < ch) continue;
            ll t1 = dp[i][j - 1] == LM ? LM : grid[i][j] - ch + dp[i][j - 1];
            ll t2 = dp[i - 1][j] == LM ? LM : grid[i][j] - ch + dp[i - 1][j];
            if(i == 1 && j == 1) dp[i][j] = grid[i][j] - h;
            else dp[i][j] = min(t1, t2);
        }
    }
    return dp[n][m];
}

void solve() {
    ll ans = LM;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ll h = grid[i][j] - (i + j - 2);
            ans = min(ans, cal(h));
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++)
                cin >> grid[i][j];
        }
        solve();
    }
};