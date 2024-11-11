/**
 * @Time : 2024/7/31-10:28 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1675F 深度优先搜索
 */
 /*
  * 观察用例 发现从x到y到路径 不用走回头路
  * 从这个路径到任务点 全都需要走回头路
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, x, y, task[N], path[N];
vector<vector<int>> graph;

int dfs1(int v, int f) {
    if(v == y) return path[y] = 0;
    if(graph[v].size() == 1 && f != -1) return -1;
    for(int w : graph[v]) {
        if(w == f) continue;
        int t = dfs1(w, v);
        if(t >= 0) return path[v] = t + 1;
    }
    return -1;
}

int dfs(int v, int f) {
    if(graph[v].size() == 1 && f != -1) return 0;
    int cnt = 0;
    for(int w : graph[v]) {
        if(path[w] != -1 || w == f) continue;
        cnt += dfs(w, v);
        if(task[w] == 1) task[v] = 1, cnt++;
    }
    return cnt;
}

void solve() {
    int ans = dfs1(x, -1);
    for(int i = 1; i <= n; i++) {
        if(path[i] == -1) continue;
        ans += 2 * dfs(i, -1);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> x >> y;
        graph.assign(n + 1, {});
        fill(task, task + n + 1, 0), fill(path, path + n + 1, -1);
        for(int i = 1, node; i <= k; i++) {
            cin >> node;
            task[node] = 1;
        }
        for(int i = 1, v , w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        solve();
    }
};