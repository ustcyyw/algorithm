/**
 * @Time : 2024/11/16-11:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1933F BFS 思维 2100
 */
 /*
  * 在某个点(x,y)时 如果是向上移动 那么和[y, m]这些列的石头的相对位置没有任何变化
那在y垂直移动、到后续的列[y + 1, m]再垂直移动 没有本质区别 那完全可以到达后续的列再垂直移动
所以只有向下移动有意义 向下移动一次 与此同时[y, m]列上的石头向上移动一格 人和石头的相对位置变化2
特殊地 在最后一列运行向上移动
明确了移动方向 也就是除了最后一列可以向上移动 其它列只能向右、向下移动

但是还要考虑石头的阻碍 假设在第time秒到达(x,y) 忽略取mod的前提下
下一次移动如果是向下 那么(x + 1, y), (x + 2, y)处不能有石头
下一次移动如果是向右 那么(x + 1, y + 1)处不能有石头
因为石头动态移动 不能每次都去更新石头的位置
但是可以倒推 如果横坐标x + 1、x + 2处有石头 那么time秒之前他们在哪
假设石头原本在 x0位置 经time秒 其位置在x处，也就是 ((x0 - time) % n + n) % n = x
可以解出来 x0 = ((x + time) % n + n) % n
于是只要看相应的列 一开始第x0行是否有石头即可

  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e3 + 5;
int T, n, m, grid[N][N];
vector<vector<int>> marked;
vector<set<int>> stones;

int base_pos(int x, int time) {
    return ((x + time) % n + n) % n;
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