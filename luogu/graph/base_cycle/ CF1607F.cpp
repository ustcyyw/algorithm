/**
 * @Time : 2024/7/19-11:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1607F 基环数 bfs
 */
/*
 * 一个点只能走向一个方向 如果将点的关系用边连起来 就是一个有向图
 * 由于出度都是1 图中只有简单还 因此这是一个基环树（森林）
 * 那么图中的点 要么走出边界 要么走进环中
 * 所以可以先用拓扑排序找到环 并且求出环的长度
 * 然后再算走到环中的树枝长度和走到边界外的路径长度
 * ps 由于出度为1 所以某个点要么是最后走进环 要么走到边界外
 *
 * dfs会卡空间的毒瘤题
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 4e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, ans, px, py, degree[N], depth[N];
string s[2005];
vector<int> graph;
vector<vector<int>> rg;

void build() {
    graph.assign(n * m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = i, y = j;
            if (s[i][j] == 'L') y--;
            if (s[i][j] == 'R') y++;
            if (s[i][j] == 'U') x--;
            if (s[i][j] == 'D') x++;
            if (x < 0 || y < 0 || x >= n || y >= m) continue;
            graph[i * m + j] = x * m + y, degree[x * m + y]++;
        }
    }
}

void build_rg() {
    rg.assign(n * m, {});
    for(int i = 0; i < n * m; i++) {
        int w = graph[i];
        if(w != -1 && degree[i] == 0) rg[w].push_back(i);
    }
}

void topol_bfs() {
    queue<int> queue;
    for (int i = 0; i < n * m; i++)
        if (degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front();
        queue.pop();
        int w = graph[v];
        if (w != -1 && --degree[w] == 0)
            queue.push(w);
    }
}

int dfs1(int v, int& start, int cnt) {
    if (graph[v] == start)
        return depth[v] = cnt;
    return depth[v] = dfs1(graph[v], start, cnt + 1);
}

void solve() {
    build();
    topol_bfs();
    // 计算环中结点个数
    for (int i = 0; i < n * m; i++) {
        if (degree[i] > 0 && depth[i] == 0) dfs1(i, i, 1);
    }
    // 用枚举非环中结点找最大值
    build_rg();
    queue<int> queue;
    for(int i = 0; i < n * m; i++) {
        if(degree[i] > 0) queue.push(i);
        if(graph[i] == -1) depth[i] = 1, queue.push(i);
    }
    while (queue.size()) {
        int v = queue.front();
        queue.pop();
        for(int w : rg[v]) {
            if (w != -1)
                queue.push(w), depth[w] = depth[v] + 1;
        }
    }
    for (int i = 0; i < n * m; i++) {
        if (depth[i] > ans) {
            ans = depth[i];
            px = i / m + 1, py = i % m + 1;
        }
    }
    cout << px << " " << py << " " << ans << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        ans = -1;
        fill(degree, degree + (m * n), 0), fill(depth, depth + (m * n), 0);
        for (int i = 0; i < n; i++)
            cin >> s[i];
        solve();
    }
};