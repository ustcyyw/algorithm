/**
 * @Time : 2024/9/11-11:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : lc3283 状态压缩dp bfs
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2505, T = 50, M = (1 << 15) + 5;
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dis[N][N], marked[T][T];

void bfs(int x1, int y1) {
    queue<int> queue;
    memset(marked, 0, sizeof(marked));
    int k = x1 * T + y1;
    queue.push(k), dis[k][k] = 0, marked[x1][y1] = 1;
    int step = 1;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz--) {
            int val = queue.front(); queue.pop();
            int x = val / T, y = val % T;
            for(int i = 0; i < 8; i++) {
                int nx = x + dx[i], ny = y + dy[i], nk = nx * T + ny;
                if(nx < 0 || ny < 0 || nx >= T || ny >= T || marked[nx][ny]) continue;
                dis[k][nk] = dis[nk][k] = step;
                marked[nx][ny] = 1, queue.push(nk);
            }
        }
        step++;
    }
}

int init = []() -> int{
    for(int i = 0; i < T; i++) {
        for(int j = 0; j < T; j++)
            bfs(i, j);
    }
    return 0;
}();

class Solution {
public:
    int n, full, cache[16][M], pos[20][2];

    int dfs(int sI, int s) {
        if(s == 0) return 0;
        if(cache[sI][s] != 0) return cache[sI][s];
        int x1 = pos[sI][0], y1 = pos[sI][1], k1 = x1 * T + y1;
        int flag = (n - __builtin_popcount(s)) % 2 == 0; // 吃了偶数个棋子 轮到alice走
        int ans = flag ? INT_MIN : INT_MAX; // flag = 1 表示要取最大
        for(int i = 0; i < n; i++) {
            int t = 1 << i;
            if(t & s) {
                int x2 = pos[i][0], y2 = pos[i][1], k2 = x2 * T + y2;
                int tempD = dis[k1][k2] + dfs(i, s ^ t);
                ans = flag ? max(ans, tempD) : min(ans, tempD);
            }
        }
        return cache[sI][s] = ans;
    }

    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        n = positions.size(), full = (1 << n) - 1;
        positions.push_back({kx, ky}); // 起点视为编号为n的点
        for(int i = 0; i <= n; i++)
            pos[i][0] = positions[i][0], pos[i][1] = positions[i][1];
        for(int i = 0; i <= n; i++)
            fill(cache[i], cache[i] + full + 1, 0);
        for(auto& pos : positions)
            bfs(pos[0], pos[1]);
        // 起点视为编号为n的点
        return dfs(n, full);
    }
};