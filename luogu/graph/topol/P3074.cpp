/**
 * @Time : 2023/5/12-3:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 拓扑排序算最长路径 引入超级起点和超级终点
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int n, m, times[N];
long long dist[N];
vector<int> order;
vector<vector<vector<int>>> graph;

void topol_sort(){
    vector<int> degree(n + 3, 0);
    for(int v = 1; v <= n + 2; v++) {
        for(auto& edge : graph[v])
            degree[edge[0]]++;
    }
    queue<int> queue;
    queue.push(n + 1);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        order.push_back(v);
        for(auto& edge : graph[v])
            if(--degree[edge[0]] == 0) queue.push(edge[0]);
    }
}

void relax(int v) {
    for(auto& edge : graph[v]) {
        int w = edge[0], c = edge[1];
        if(dist[w] < dist[v] + c)
            dist[w] = dist[v] + c;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    graph.assign(n + 3, {});
    int s = n + 1, e = n + 2;
    for(int i = 1, t; i <= n; i++) {
        cin >> t;
        times[i] = t;
        graph[s].push_back({i, 0}), graph[i].push_back({e, t});
    }
    for(int i = 0, v, w; i < m; i++) {
        cin >> v >> w;
        graph[v].push_back({w, times[v]});
    }
    topol_sort();
    memset(dist, 0, sizeof(dist));
    for(int v : order)
        relax(v);
    cout << dist[e] << endl;
}