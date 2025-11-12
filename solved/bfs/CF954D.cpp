/**
 * @Time : 2025/3/19-10:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF954D 1600 bfs
 */
/*
  * 先从s出发 dis1[i]: s到达结点i的最短路径长度
  * 再从t出发 dis2[i]: t到达结点i的最短路径长度
  * 假设连通一条边
  * 使得 dis1[a] + 1 + dis2[b] < dis1[t]
  * 那么从 s -> a -> b -> t 的路径长度会缩短
  * 或者 dis1[b] + 1 + dis2[a] < dis1[t]
  * 那么从 s -> b -> a -> t 的路径长度会缩短
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1005, mod = 1e9 + 7;
int T, n, m, s, t, dis1[N], dis2[N];
set<int> edges;
vector<int> graph[N];

void bfs(int start, int* dis) {
    queue<int> queue;
    queue.push(start), dis[start] = 0;
    while(!queue.empty()) {
        int v = queue.front(), nd = dis[v] + 1; queue.pop();
        for(int w : graph[v]) {
            if(dis[w] > nd)
                dis[w] = nd, queue.push(w);
        }
    }
}

void solve() {
    bfs(s, dis1), bfs(t, dis2);
    int d = dis1[t];
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(edges.count(i * N + j)) continue;
            int a = i, b = j;
            if(!(dis1[a] + 1 + dis2[b] < d || dis1[b] + 1 + dis2[a] < d)) cnt++;
        }
    }
    cout << cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> s >> t;
    fill(dis1 + 1, dis1 + n + 1, INT_MAX), fill(dis2 + 1, dis2 + n + 1, INT_MAX);
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        if(v > w) swap(v, w);
        edges.insert(v * N + w);
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
}