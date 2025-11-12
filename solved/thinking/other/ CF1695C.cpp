/**
 * @Time : 2024/6/6-1:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1695C 思维 动态规划
 */
/*
 * n * m <= 1000
 * 只有1和-1 最多能走 n + m - 1 个格子  n + m - 1 为偶数
 * 路径上的-1, 和1 必须都是 n + m - 1 / 2 个
 * 因为总的格子数是n + m - 1为偶数，假设有某条路径有k个1，(n + m - 1 - k)个-1
 * 路径和为 k - (n + m - 1 - k) = 2k - (n + m - 1) 是偶数
 * 因此就确定了 路径和一定是偶数
 * 假设某一条路径的和为x 通过一次调整（参考图来看）
 * 比如在某个点本来是先右再下 改成先下再右 新的路径和老路径只有2个格子不同
 * 两个格子可能都是1或者都是-1，那么路径和不变
 * 两个格子可能 旧的是1，新的是-1 路径和-2，或者反之路径和+2
 * 因此发现通过调整 路径和只有三种可能+2，-2，0的变化
 * 于是求出路径的最大和、最小和之和 看0是否在二者之间 如果在
 * 就能通过将最大路径（或者最小路径）通过调整找到和为0的路径
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e3 + 5, MV = 1e9;
typedef long long ll;
int T, n, m, k, grid[N][N], dp1[N][N], dp2[N][N];

bool solve() {
    if((n + m - 1) % 2 == 1) return false;
    dp1[1][1] = dp2[1][1] = grid[1][1];
    for(int i = 2; i <= m; i++)
        dp1[1][i] = dp2[1][i] = dp1[1][i - 1] + grid[1][i];
    for(int i = 2; i <= n; i++)
        dp1[i][1] = dp2[i][1] = dp1[i - 1][1] + grid[i][1];
    for(int i = 2; i <= n; i++) {
        for(int j = 2; j <= m; j++) {
            dp1[i][j] = max(dp1[i - 1][j], dp1[i][j - 1]) + grid[i][j];
            dp2[i][j] = min(dp2[i - 1][j], dp2[i][j - 1]) + grid[i][j];
        }
    }
    return dp2[n][m] <= 0 && dp1[n][m] >= 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++)
                cin >> grid[i][j];
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};