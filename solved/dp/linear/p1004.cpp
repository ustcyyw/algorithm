/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

/*
 * 走两遍 可能会出现两条路径有交点
 * 交点意味着两次出发走到这个地方用的步数一致 那么走两遍等价于两个人同时出发 一共收集到多少
 * 坐标和步数之间有映射关系 知道走了多少步 且知道行坐标 就能知道列坐标
 * 注意：坐标从1到n
 *
 * 定义dp[k][x1][x2]: 表示单个人走了k步（横纵坐标之和）时，两个人的横坐标分别为x1，x2的最大值
 * dp[k]由走了k-1步的dp[k-1]转移而来
 * 只能向下和右走 那么两个人就有4种方向组合
 * 都向下走 dp[k-1][x1-1][x2-1] -> dp[k][x1][x2]
 * 第一个人向下走，第二个人向右走 dp[k-1][x1-1][x2] -> dp[k][x1][x2]
 * 第一个人向右走，第二个人向下走 dp[k-1][x1][x2-1] -> dp[k][x1][x2]
 * 都向右走 dp[k-1][x1][x2] -> dp[k][x1][x2]
 *
 * 边界条件 dp[2][1][1] = grid[1][1] : 起点坐标是(1,1)
 * 答案 dp[2*n][n][n] : 终点坐标是(n,n)
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 11;
int n, x, y, num, grid[N][N];

int solve() {
    vector<vector<vector<int>>> dp(2 * n + 1, vector(n + 1, vector(n + 1, 0)));
    dp[2][1][1] = grid[1][1];
    for(int k = 3; k <= 2 * n; k++) {
        for(int x1 = max(1, k - n); x1 <= min(k - 1, n); x1++) {
            for(int x2 = max(1, k - n); x2 <= min(k - 1, n); x2++) {
                int y1 = k - x1, y2 = k - x2;
                dp[k][x1][x2] = max({dp[k-1][x1-1][x2-1], dp[k-1][x1-1][x2],
                                     dp[k-1][x1][x2-1], dp[k-1][x1][x2]}) + grid[x1][y1];
                if(x1 != x2) dp[k][x1][x2] += grid[x2][y2];
            }
        }
    }
    return dp[2 * n][n][n];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(grid, 0, size(grid));
    cin >> n;
    while (true) {
        cin >> x >> y >> num;
        if(num == 0) break;
        grid[x][y] = num;
    }
    cout << solve() << endl;
}