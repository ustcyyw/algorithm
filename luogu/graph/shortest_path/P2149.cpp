/**
 * @Time : 2023/5/26-10:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 先用第一个人跑dijk找出所有可能的最短路
 * 然后根据到达终点的所有可能的最短路建图，得到公共路径的备选边 不在这个图中的边 都不是公共边
 *
 * 第二个人跑dijk的时候 就是动态规划
 * common[w]表示：到达w的最短路径中，公共路径最长的长度是多少
 * 最短路径可能有多条边到达w，就选择到w公共路径最长到。
 *
 * 注意本题中 公共路径 可以同向 可以逆向
 * 在上一个步骤中建图得到的是有向图，因此在第二遍dijk中 计算公共路径长度的时候
 * 判断条件应该是 graph[w].count(v) || graph[v].count(w)
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1505;
const long max_val = 1e12;
int n, m, x, y, a, b, marked1[N], marked2[N];
long dist1[N], dist2[N], common[N], grid[N][N];
vector<unordered_set<int>> path, graph;

void dijkstra1(int s, int e) {
    dist1[s] = 0;
    for(int i = 1; i <= n && !marked1[e]; i++) {
        long val = max_val; int v = -1;
        for(int j = 1; j <= n; j++) { // 找到当前距离最小的点 就是这一轮添加到最短路径树中的点
            if(marked1[j]) continue;
            val = min(val, dist1[j]);
            if(dist1[j] == val) v = j;
        }
        marked1[v] = true;
        for(int w = 1; w <= n; w++) { // 放缩
            if(grid[v][w] == max_val) continue;
            if(dist1[w] > dist1[v] + grid[v][w]) {
                dist1[w] = dist1[v] + grid[v][w];
                path[w] = {};
                path[w].insert(v);
            } else if(dist1[w] == dist1[v] + grid[v][w])
                path[w].insert(v);
        }
    }
}

void dijkstra2(int s, int e) {
    dist2[s] = 0;
    for(int i = 1; i <= n && !marked2[e]; i++) {
        long val = max_val; int v = -1;
        for(int j = 1; j <= n; j++) { // 找到当前距离最小的点 就是这一轮添加到最短路径树中的点
            if(marked2[j]) continue;
            val = min(val, dist2[j]);
            if(dist2[j] == val) v = j;
        }
        marked2[v] = true;
        for(int w = 1; w <= n; w++) { // 放缩
            if(grid[v][w] == max_val) continue;
            if(dist2[w] > dist2[v] + grid[v][w]) {
                dist2[w] = dist2[v] + grid[v][w];
                common[w] = common[v] + (graph[w].count(v) || graph[v].count(w) ? grid[v][w] : 0);
            } else if(dist2[w] == dist2[v] + grid[v][w]) {
                long t = common[v] + (graph[w].count(v) || graph[v].count(w) ? grid[v][w] : 0);
                common[w] = max(common[w], t);
            }
        }
    }
}

void build(int e) {
    for(int w : path[e]) {
        if(graph[e].count(w)) return;
        graph[e].insert(w);
        build(w);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m >> x >> y >> a >> b;
    fill(marked1, marked1 + n + 1, 0), fill(marked2, marked2 + n + 1, 0);
    fill(dist1, dist1 + n + 1, max_val), fill(dist2, dist2 + n + 1, max_val);
    fill(common, common + n + 1, 0);
    for(int i = 1; i <= n; i++)
        fill(grid[i], grid[i] + n + 1, max_val);
    path.assign(n + 1, {}), graph.assign(n + 1, {});
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        grid[u][v] = grid[v][u] = w;
    }
    dijkstra1(x, y);
    // 求第一个人走到终点的所有可能的最短路构成的图
    build(y);
    dijkstra2(a, b);
    cout << common[b] << endl;
}