/**
 * @Time : 2024/1/25-8:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 问题等价于一个人向右下走 一个人向左上走 并且走相同的步数 类似于两个人一起摘樱桃题
 * f[i][r1][r2]: 走了i步 并且两个人的行坐标分别为c1,c2时 构成回文对称的路径数
 * 从起点到终点（或者从终点到起点）总步数 step = n + m - 2
 * c1 = i - r1, c2 = n + m - 2 - i - r2
 * c1 <= m - 1 --> i - r1 <= m - 1, r1 >= i - m + 1
 * c2 <= m - 1 --> n + m - 2 - i - r2 <= m - 1, r2 >= n - 1 - i
 * c2 >= 0 --> n + m - 2 - i - r2 >= 0, r2 <= n + m - 2 - i
 * 要求 r1 <= min(i, n - 1), r2 <= min(n - 1, n + m - 2 - i)
 *
 * 当走到第i步时
 * 如果grid[r1][c1] != grid[r2][c2]时 f[i][r1][r2] = 0
 * 否则 如果第i-1步时 有回文对称路径 并且可以一步走到当前点
 * 那么其作为前缀加上当前点就是长度+1的回文对称路径数
 * f[i][r1][r2] = f[i-1][r1][r2] + f[i-1][r1-1][r2] + f[i-1][r1][r2+1] + f[i-1][r1-1][r2+1]
 * 注意  对于第一个人来说 上一步的行号不变或者-1；对于第2个人来说 上一步的行号不变或者+1
 * 如果r1先计算大的值，r2先计算小的值 就能进行滚动优化 压缩空间
 *
 * 初条件 grid[0][0] != grid[n - 1][m - 1] 直接return
 * 否则 f[0][0][n - 1] = 1
 *
 * 答案 如果走的总步数是奇数 两人的行号可能相等 可能相差1（得出回文串时 两个人相差一步的距离）
 * 否则 两个人的行号相等（得出回文串时 两人在同一个点）
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 505, mod = 1e9 + 7;
int n, m;
string grid[N];

long long solve() {
    if(grid[0][0] != grid[n - 1][m - 1]) return 0;
    if(m + n <= 3) return 1; // 只用走一步或者0步的情况
    vector<vector<long long>> dp(n, vector(n, 0ll));
    dp[0][n - 1] = 1;
    int step = n + m - 2;
    for(int i = 1; i <= step / 2; i++) {
        for(int r1 = min(i, n - 1); r1 >= max(i - m + 1, 0); r1--) {
            for(int r2 = max(n - 1 - i, 0); r2 <= min(n + m - 2 - i, n - 1); r2++) {
                int c1 = i - r1, c2 = n + m - 2 - i - r2;
                if(grid[r1][c1] != grid[r2][c2]) {
                    dp[r1][r2] = 0;
                    continue;
                }
                // dp[r1][r2] = dp[r1][r2] + dp[r1-1][r2] + dp[r1][r2+1] + dp[r1-1][r2+1];
                if(r1 - 1 >= 0) dp[r1][r2] += dp[r1 - 1][r2];
                if(r2 + 1 <= n - 1) dp[r1][r2] += dp[r1][r2 + 1];
                if(r1 - 1 >= 0 && r2 + 1 <= n - 1) dp[r1][r2] += dp[r1 - 1][r2 + 1];
                dp[r1][r2] %= mod;
            }
        }
    }
    long long res = 0;
    for(int i = 0; i < n; i++) {
        res += dp[i][i];
        if(step % 2 == 1 && i + 1 < n) res += dp[i][i + 1];
    }
    return res % mod;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> grid[i];
    cout << solve() << endl;
}