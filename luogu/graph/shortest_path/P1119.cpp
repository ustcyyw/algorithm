/**
 * @Time : 2023/5/8-12:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 205, M = N * N / 2, max_val = 1e9 + 5;
int n, m, q, times[N];
vector<vector<int>> dis;

void add_edge(vector<int>& edge) {
    int v = edge[0], w = edge[1], cost = edge[2];
    if(dis[v][w] <= cost) return;
    dis[v][w] = min(dis[v][w], cost);
    dis[w][v] = min(dis[w][v], cost);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // 考虑从经过路径 i -> v -> w -> j能否缩短距离
            dis[i][j] = min(dis[i][j], dis[i][v] + cost + dis[w][j]);
            dis[i][j] = min(dis[i][j], dis[i][w] + cost + dis[v][j]);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    dis = vector(n, vector(n, max_val));
    for(int i = 0; i < n; i++) dis[i][i] = 0;
    for(int i = 0, t; i < n; i++) {
        cin >> t;
        times[i] = t;
    }
    vector<vector<int>> edges;
    for(int i = 0, v, w, t; i < m; i++) {
        cin >> v >> w >> t;
        edges.push_back({v, w, t, max(times[v], times[w])});
    }
    sort(edges.begin(), edges.end(),
         [](auto& a, auto& b) -> bool { return a[3] < b[3];});
    cin >> q;
    for(int i = 0, x, y, t, j = 0; i < q; i++) {
        cin >> x >> y >> t;
        while (j < m && edges[j][3] <= t)
            add_edge(edges[j++]);
        if(dis[x][y] == max_val) cout << -1 << endl;
        else cout << dis[x][y] << endl;
    }
}