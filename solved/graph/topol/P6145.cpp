/**
 * @Time : 2023/5/12-5:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, c, dist[N];
vector<int> order;
vector<vector<vector<int>>> graph;

void topol_sort(){
    vector<int> degree(n + 2, 0);
    for(int v = 1; v <= n + 1; v++) {
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
    for(auto& edge : graph[v]){
        int w = edge[0], cost = edge[1];
        if(dist[w] < dist[v] + cost)
            dist[w] = dist[v] + cost;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m >> c;
    fill(dist, dist + n + 1, 0);
    graph.assign(n + 2, {});
    for(int i = 1, s = n + 1, t; i <= n; i++){
        cin >> t;
        dist[i] = t;
        graph[s].push_back({i, 0});
    }
    for(int i = 1, a, b, x; i <= c; i++) {
        cin >> a >> b >> x;
        graph[a].push_back({b, x});
    }
    topol_sort();
    for(int v : order)
        relax(v);
    for(int i = 1; i <= n; i++)
        cout << dist[i] << endl;
}