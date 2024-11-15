/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e3 + 5;
int T, n, m, grid[N][N];
vector<vector<int>> marked;
vector<set<int>> stones;

int base_pos(int y, int time) {
    return ((y + time) % n + n) % n;
}

void add(queue<vector<int>>& queue, int x, int y) {
    queue.push({x, y}), marked[x][y] = 1;
}

int solve() {
    queue<vector<int>> queue;
    int step = 0;
    queue.push({0, 0});
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz--) {
            int x = queue.front()[0], y = queue.front()[1];
            if (x == n - 1 && y == m - 1) return step;
            queue.pop();
            if (y == m - 1 && !marked[(x - 1 + n) % n][y]) add(queue, (x - 1 + n) % n, y); // 在最后一列才有向上走的必要
            // 计算到达此点时 x+1和x+2有石头的话 初始时刻的坐标
            int p1 = base_pos(x + 1, step), p2 = base_pos(x + 2, step);
            // 向下走
            if (!marked[(x + 1) % n][y] && !stones[y].count(p1) && !stones[y].count(p2))
                add(queue, (x + 1) % n, y);
            // 向右走
            if (y + 1 < m && !marked[x][y + 1] && !stones[y + 1].count(p1))
                add(queue, x, y + 1);
        }
        step++;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m;
        stones.assign(m, {});
        marked.assign(n, vector(m, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> grid[i][j];
                if(grid[i][j]) stones[j].insert(i);
            }
        }
        cout << solve() << "\n";
    }
};