/**
 * @Time : 2023/10/13-9:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 按题目的方向 走到右下 再走到左上 两条路径
 * 和从左上起点走到右下终点 走两条没有区别
 * 两条路径不允许有交点 因为同一个人不能传递两次 既然两条路径不能有交点，那么先后出发和同时出发没有区别
 * 以同时出发来考虑
 * 注意：坐标从1到n
 *
 * 定义dp[k][x1][x2]: 表示单个人走了k步（横纵坐标之和）时，两个人的横坐标分别为x1，x2的最大值
 * dp[k]由走了k-1步的dp[k-1]转移而来
 * 只能向下和右走 那么两个人就有4种方向组合
 * 都向下走 dp[k-1][x1-1][x2-1] -> dp[k][x1][x2]
 * 第一个人向下走，第二个人向右走 dp[k-1][x1-1][x2] -> dp[k][x1][x2]
 * 第一个人向右走，第二个人向下走 dp[k-1][x1][x2-1] -> dp[k][x1][x2]
 * 都向右走 dp[k-1][x1][x2] -> dp[k][x1][x2]
 * 但是当x1 == x2时 两条路径相交，这种情况不允许 直接设置为-1 表示不可能
 *
 * 边界条件 dp[2][1][1] = grid[1][1] : 起点坐标是(1,1)
 * 答案 dp[2*n][n][n] : 终点坐标是(n,n)
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int n, m, grid[N][N];

int solve() {
    vector<vector<vector<int>>> dp(n + m + 1, vector(n + 1, vector(n + 1, 0)));
    for(int k = 3; k <= n + m; k++) {
        for(int x1 = max(1, k - m); x1 <= min(k - 1, n); x1++) {
            for(int x2 = max(1, k - m); x2 <= min(k - 1, n); x2++) {
                int y1 = k - x1, y2 = k - x2;
                // 非终点以外的其它情况下 x1 = x2，一定有y1 = y2 两个点重合了 不可取
                if(x1 == x2 && !(x1 == n && y1 == m))
                    continue;
                if(x1 - 1 != x2) dp[k][x1][x2] = dp[k-1][x1-1][x2];
                if(x1 != x2 - 1) dp[k][x1][x2] = max(dp[k][x1][x2], dp[k-1][x1][x2-1]);
                dp[k][x1][x2] = max({dp[k-1][x1-1][x2-1], dp[k][x1][x2], dp[k-1][x1][x2]})
                                + grid[x1][y1] + grid[x2][y2];
            }
        }
    }
    return dp[n + m][n][n];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }
    cout << solve() << endl;
}