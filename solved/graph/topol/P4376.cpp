/**
 * @Time : 2023/5/26-5:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 二分 + 最小优先队列的拓扑
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
int n, m, degree[N];
vector<vector<int>> infos;
vector<unordered_set<int>> graph;

void build(int t) {
    fill(degree, degree + n + 1, 0);
    graph.assign(n + 1, {});
    for (int i = 0; i < t; i++) {
        vector<int> &info = infos[i];
        for (int j = 0; j < (int) info.size() - 1; j++) {
            graph[info[j]].insert(info[j + 1]);
            degree[info[j + 1]]++;
        }
    }
}

void cal_degree() {
    fill(degree, degree + n + 1, 0);
    for (int v = 1; v <= n; v++) {
        for (int w: graph[v])
            degree[w]++;
    }
}

bool check(int t) {
    int cnt = 0;
    build(t), cal_degree();
    queue<int> queue;
    for (int v = 1; v <= n; v++)
        if (degree[v] == 0) queue.push(v);
    while (queue.size()) {
        int v = queue.front();
        queue.pop(), cnt++;
        for (int w: graph[v])
            if (--degree[w] == 0) queue.push(w);
    }
    return cnt == n;
}

void topol_bfs(int t) {
    build(t), cal_degree();
    priority_queue<int, vector<int>, greater<>> queue;
    for (int i = 1; i <= n; i++)
        if (degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.top();
        queue.pop();
        for (int w: graph[v])
            if (--degree[w] == 0) queue.push(w);
        if (queue.empty()) cout << v << endl;
        else cout << v << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    infos.assign(0, {});
    for (int i = 1, t; i <= m; i++) {
        cin >> t;
        vector<int> temp;
        for (int j = 1, v = -1; j <= t; j++) {
            cin >> v;
            temp.push_back(v);
        }
        infos.push_back(temp);
    }
    int lo = 1, hi = m;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    topol_bfs(lo);
}