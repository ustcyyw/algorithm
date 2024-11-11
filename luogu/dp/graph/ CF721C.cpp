/**
 * @Time : 2023/12/5-4:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int n, m, T, conn[N], degree[N];
vector<vector<int>> edges;
vector<vector<vector<int>>>graph;

void checkDis(int s) {
    memset(conn, 0, sizeof(conn));
    function<void(int)> dfs = [&](int v) -> void {
        conn[v] = 1;
        for(auto& edge : graph[v]) {
            if(!conn[edge[1]])
                dfs(edge[1]);
        }
    };
    dfs(s);
}

void rebuild() {
    memset(degree, 0, sizeof(degree));
    graph.assign(n + 1, {});
    for(auto& edge : edges) {
        int a = edge[0], b = edge[1];
        if(conn[a] && conn[b]) {
            degree[b]++;
            graph[a].push_back(edge);
        }
    }
}

void topol(vector<unordered_map<int, int>>& dp, vector<vector<int>>& path) {
    // dp[i][j]: 到达第i点 路径上共有j个点的最短距离
    dp.assign(n + 1, {});
    queue<int> queue;
    dp[1][1] = 0, queue.push(1);
    while(queue.size()) {
        int v = queue.front();
        for(auto& edge : graph[v]) {
            int w = edge[1], d = edge[2];
            for(auto& pair : dp[v]) {
                if(d + pair.second <= T) {
                    int cnt = pair.first + 1;
                    if(!dp[w].count(cnt) || d + pair.second < dp[w][cnt]) {
                        dp[w][cnt] = d + pair.second;
                        path[w][cnt] = v;
                    }
                }
            }
            if(--degree[w] == 0) {
                if(w == n) return ;
                queue.push(w);
            }
        }
        queue.pop();
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> T;
    graph.assign(n + 1, {});
    for(int i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
        graph[a].push_back({a, b, w});
    }
    checkDis(1);
    rebuild();
    vector<unordered_map<int, int>> dp;
    vector<vector<int>> path(n + 1, vector(n + 1, -1));
    topol(dp, path);
    int res = 0, node = n;
    for(auto& p : dp[n])
        res = max(res, p.first);
    cout << res << endl;
    vector<int> nodes;
    while(res > 0) {
        nodes.push_back(node);
        node = path[node][res--];
    }
    for(int i = nodes.size() - 1; i >= 0; i--)
        cout << nodes[i] << " ";
}