/**
 * @Time : 2024/6/27-10:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1851G 离线思想 并查集
 */
 /*
  * 从某个点为起点 i -> j, cost = h[j] - h[i]
如果h[j] < h[i], 就是在下降 会恢复能量
如果h[j] > h[i], 在爬升 会消耗能量

1 4 2 5 3
-3 +2 -3 +2
-3 -1 -4 -2
在最终能到达的情况下，到达某点的能量变化只与高度差有关
并且只要能跨过最高峰就可以保证到达终点

那么考虑从高度低的点开始枚举 看看在最高峰为h[k]的情况下 哪些结点可以跨越
e + h[s] >= h[k], 并且此时s和t两个点都在同一个连通分量里面了

将h排序 将e + h[s]排序
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, m, Q, h[N], id[N];
string ans[N];
vector<vector<int>> nodes, graph, infos;

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return;
    id[p] = q;
}

void solve() {
    for(int i = 0, j = 0; i < Q; i++) {
        int e = infos[i][0], p = infos[i][1], q = infos[i][2], idx = infos[i][3];
        while(j < n && nodes[j][0] <= e) {
            int v = nodes[j][1];
            for(int w : graph[v]) {
                if(h[w] <= e) connect(v, w);
            }
            j++;
        }
        ans[idx] = find(p) == find(q) ? "YES" : "NO";
    }
    for(int i = 1; i <= Q; i++)
        cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        nodes = {}, infos = {}, graph.assign(n + 1, {});
        for(int i = 1; i <= n; i++) {
            cin >> h[i];
            nodes.push_back({h[i], i});
            id[i] = i;
        }
        sort(nodes.begin(), nodes.end());
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cin >> Q;
        for(int i = 1, s, t, e; i <= Q; i++) {
            cin >> s >> t >> e;
            infos.push_back({h[s] + e, s, t, i});
        }
        sort(infos.begin(), infos.end());
        solve();
    }
};