/**
 * @Time : 2023/5/9-10:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * floyd 动态加边
 * 注意如果是无向边 要 考虑 i -> v -> w -> j 和 i -> w -> v -> j 的两种路径
 */
#include<bits/stdc++.h>
using namespace std;

int n, m, x, max_val = 1e9;
vector<vector<int>> dist;

void add_edge(vector<int>& edge){
    int v = edge[0], w = edge[1], l = edge[2];
    if(dist[v][w] <= l) return;
    dist[v][w] = dist[w][v] = l;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) {
            int t = min( dist[i][v] + dist[w][j], dist[i][w] + dist[v][j]) + l;
            dist[i][j] = min(dist[i][j], t);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m >> x;
    dist = vector(n + 1, vector(n + 1, max_val));
    for(int i = 1; i <= n; i++)
        dist[i][i] = 0;
    vector<vector<int>> edges;
    for(int i = 0, v, w, l, c; i < m; i++) {
        cin >> v >> w >> l >> c;
        edges.push_back({v, w, l, c});
    }
    sort(edges.begin(), edges.end(),
         [](auto& a, auto& b) -> bool {return b[3] < a[3];});
    int ans = max_val;
    for(auto& edge : edges) {
        add_edge(edge);
        if(dist[1][n] != max_val)
            ans = min(ans, dist[1][n] + x / edge[3]);
    }
    cout << ans << endl;
}