/**
 * @Time : 2024/7/7-9:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1472G 深度优先
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, d[N], ans[N], marked[N];
vector<vector<int>> graph;

void bfs() {
    queue<int> queue;
    queue.push(1), marked[1] = 1;
    int step = 0;
    while (!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front(); queue.pop();
            ans[v] = d[v] = step;
            for(int w : graph[v]) {
                if(!marked[w]) queue.push(w), marked[w] = 1;
            }
        }
        step++;
    }
}

void dfs(int v) {
    marked[v] = 1;
    for(int w : graph[v]) {
        if(d[w] <= d[v]) ans[v] = min(ans[v], d[w]);
        else {
            if(!marked[w]) dfs(w);
            ans[v] = min(ans[v], ans[w]);
        }
    }
}

void solve() {
    bfs();
    fill(marked, marked + n + 1, 0);
    dfs(1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {});
        fill(marked, marked + n + 1, 0);
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w);
        }
        solve();
    }
};