/**
 * @Time : 2023/5/12-9:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 拓扑排序 要求是是一个有向无环图
 */

vector<int> get_degree(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> degree(n, 0);
    for(int v = 0; v < n; v++) {
        for(int w : graph[v])
            degree[w]++;
    }
    return degree;
}

vector<int> topol_dfs(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> ans, degree = get_degree(graph);
    vector<bool> marked(n, false);
    function<void(int)> dfs = [&](int v) {
        marked[v] = true;
        for(int w : graph[v])
            if(!marked[w]) dfs(w);
        ans.push_back(v);
    };
    for(int i = 0; i < n; i++){
        if(degree[i] == 0)
            dfs(i);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

vector<int> topol_bfs(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> ans, degree(n, 0);
    for(int v = 0; v < n; v++) {
        for(int w : graph[v])
            degree[w]++;
    }
    queue<int> queue;
    for(int i = 0; i < n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        ans.push_back(v);
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
    return ans;
}