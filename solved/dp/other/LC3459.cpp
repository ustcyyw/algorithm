/**
 * @Time : 2025/2/16-2:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3459 动态规划 暴力枚举
 */
 /*
  * 首先定义四个放心 1.左上, 2.右上, 3.右下, 4.左下
  * 先预处理从某个点出发 从四个方向上走02交替的序列最长能走多远 并且记录是否能走到1-2两个连续的点
  * 因为题目要求的路径一定是以1为起点，并且立马要走到2 然后才开始2020的交替
  * dp[i][j][k]：以(i,j)为起点 从k方向上走到1或者边界 经历多少个点
  * hasOne[i][j][k]：以(i,j)为起点 从k方向上是否能走到1-2的连续两个点
  * 预处理完之后 暴力枚举路径上发生90度转折的点
  * 不发生转折的情况，在那条路径的终点处 如果能转折 路径会更长
  * 如果不能转折 说明转过去方向之后第二部分路径长度为0
  * 因此不用刻意去考虑不转折的情况
  *
  * 注意路径的合法性 对于(i,j)点，枚举其第一个转折的方向k1 一定是要hasOne为1的
  * 表示是从起点1出发经过2开始进入20202的交替序列
  * 真实的路径方向 其实是k1的反方向，因此转折后的第二个方向情况依次是
  * (1->4), (2->1), (3->2), (4->2) 这一步要画方向图理解
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;
int dx[4] = {-1,-1,1,1}, dy[4] = {-1,1,1,-1};

class Solution {
public:
    int n, m;
    vector<vector<int>> grid;
    vector<vector<vector<int>>> dp, hasOne;
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        this->grid = grid;
        this->n = grid.size(), this->m = grid[0].size();
        dp = vector(n, vector(m, vector(4, -1)));
        hasOne = vector(n, vector(m, vector(4, -1)));
        bool flag = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) flag = 1;
                for(int k = 0; k < 4; k++)
                    dfs(i, j, k);
            }
        }
        if(flag == 0) return 0; // 没有开头点的情况
        int ans = 1; // 有开头点 那么至少开头点长度就是1了
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) continue;
                for(int k1 = 0; k1 < 4; k1++) {
                    if(!hasOne[i][j][k1]) continue;
                    if(k1 == 0) ans = max(dp[i][j][k1] + dp[i][j][3], ans);
                    else ans = max(dp[i][j][k1] + dp[i][j][k1 - 1], ans);
                }
            }
        }
        return ans;
    }

    void dfs(int x, int y, int k) {
        if(grid[x][y] == 1) {
            dp[x][y][k] = 0, hasOne[x][y][k] = 1;
            return;
        }
        if(dp[x][y][k] != -1) return;
        int nx = x + dx[k], ny = y + dy[k];
        if(nx < 0 || ny < 0 || nx == n || ny == m || grid[x][y] == grid[nx][ny]) {
            dp[x][y][k] = 1, hasOne[x][y][k] = 0;
            return;
        }
        dfs(nx, ny, k);
        dp[x][y][k] = dp[nx][ny][k] + 1;
        hasOne[x][y][k] = hasOne[nx][ny][k];
        if(grid[nx][ny] == 1) {
            hasOne[x][y][k] = grid[x][y] == 2;
        }
    }
};