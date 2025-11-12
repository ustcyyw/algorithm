/**
 * @Time : 2023/5/12-10:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1505;
int n, m, dist[N], max_val = 1e9;
vector<int> order, degree;
vector<vector<vector<int>>> graph;

void topol_dfs() {
    degree = vector(n + 1, 0);
    for(int v = 1; v <= n; v++) {
        for(auto& edge : graph[v])
            degree[edge[0]]++;
    }
    vector<bool> marked(n, false);
    function<void(int)> dfs = [&](int v) {
        marked[v] = true;
        for(auto& edge : graph[v])
            if(!marked[edge[0]]) dfs(edge[0]);
        order.push_back(v);
    };
    for(int i = 1; i <= n; i++){
        if(degree[i] == 0) {
            dfs(i);
            break;
        }
    }
    reverse(order.begin(), order.end());
}

void relax(int v) {
    for(auto& edge : graph[v]) {
        int w = edge[0], c = edge[1];
        if(dist[w] > dist[v] + c)
            dist[w] = dist[v] + c;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    graph.assign(n + 1, {});
    for(int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        graph[a].push_back({b, -c});
    }
    topol_dfs();
    fill(dist, dist + n + 1, max_val);
    dist[1] = 0;
    for(int v : order)
        relax(v);
    cout << (dist[n] == max_val ? -1 : -dist[n]) << endl;
}