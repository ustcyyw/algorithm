/**
 * @Time : 2024/7/10-9:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1520G bfs 暴力枚举
 */
 /*
  * 到达终点有两种方案
  * 1. 直接靠走到
  * 2. 通过一次穿越 多次穿越是无意义的 因为直接到最后到终点肯定更好
  * 所以从起点和终点各找一个综合成本（使用成本+走到该点的成本）最低的穿越点即可
  * 注意 可能走不到的情况
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e3 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m, w, grid[N][N];
vector<vector<ll>> cost1, cost2;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void bfs(int sx, int sy, vector<vector<ll>>& cost) {
    queue<vector<int>> queue;
    queue.push({sx, sy});
    cost[sx][sy] = 0;
    int step = 1;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            vector<int>& t = queue.front();
            int x = t[0], y = t[1];
            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if(nx < 1 || ny < 1 || nx > n || ny > m || grid[nx][ny] == -1) continue;
                if(cost[nx][ny] != -1 || (nx == sx && ny == sy)) continue;
                cost[nx][ny] = step * w;
                queue.push({nx, ny});
            }
            queue.pop();
        }
        step++;
    }
}

ll find(vector<vector<ll>>& cost) {
    ll ans = LONG_LONG_MAX;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(grid[i][j] > 0 && cost[i][j] != -1)
                ans = min(ans, cost[i][j] + grid[i][j]);
        }
    }
    return ans;
}

ll solve() {
    if(n == 1 && m == 1) return 0;
    bfs(1, 1, cost1);
    bfs(n, m, cost2);
    ll ans = LONG_LONG_MAX;
    if(cost1[n][m] != -1) ans = cost1[n][m];
    ll t1 = find(cost1), t2 = find(cost2);
    if(t1 != LONG_LONG_MAX && t2 != LONG_LONG_MAX)
        ans = min(t1 + t2, ans);
    return ans == LONG_LONG_MAX ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> w;
    cost1.assign(n + 1, vector(m + 1, -1ll));
    cost2.assign(n + 1, vector(m + 1, -1ll));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cin >> grid[i][j];
    }
    cout << solve();
};