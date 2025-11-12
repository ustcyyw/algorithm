/**
 * @Time : 2024/8/1-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1674G 动态规划 拓扑排序
 */
/*
 * 输入描述中说明了 图中无环 像是拓扑排序的提示
 * 题目要求的值 是一条最长的链 刚好就是按拓扑排序递归求解
 * 只不过要注意 出度 入度 为1的边必须删除 会导致会新的递归起点
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, degree[N], nd[N], cache[N];
vector<int> graph[N];
queue<int> q;

int dfs(int v) {
    if(cache[v] > 0) return cache[v];
    if(graph[v].size() <= 1) {
        if(graph[v].size() == 1) {
            int w = graph[v][0];
            if(--nd[w] == 0) q.push(w);
        }
        return cache[v] = 1;
    }
    int ans = 1;
    for(int w : graph[v]) {
        if(degree[w] == 1) {
            if(--nd[w] == 0) q.push(w);
            continue;
        }
        ans = max(ans, dfs(w) + 1);
    }
    return cache[v] = ans;
}

void solve() {
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        nd[i] = degree[i];
        if(degree[i] == 0)
            q.push(i);
    }
    while(!q.empty()) {
        int v = q.front(); q.pop();
        ans = max(ans, dfs(v));
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w);
        degree[w]++;
    }
    solve();
};