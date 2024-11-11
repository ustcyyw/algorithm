/**
 * @Time : 2023/5/10-9:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int T = 1e6, N = 501;
int n, m, max_val = 1e9, dist[N * N], marked[N * N], x, y, a, b;
char c, grid[N][N];
struct cmp {
    bool operator()(vector<int>& a, vector<int>& b){
        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
        return dist[v1] + c1 >= dist[v2] + c2;
    }
};
vector<vector<vector<int>>> graph;

void dijkstra(int s){
    fill(dist, dist + n * m + 1, max_val);
    fill(marked, marked + n * m + 1, 0);
    dist[s] = 0;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for(auto& edge : graph[v]) {
            int w = edge[1], c = edge[2];
            if(dist[w] > dist[v] + c) {
                dist[w] = dist[v] + c;
                pq.push(edge);
            }
        }
    };
    relax(s);
    while (!pq.empty()) {
        vector<int> edge = pq.top(); pq.pop();
        if(!marked[edge[1]])
            relax(edge[1]);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    while (n != 0) {
        graph.assign(n * m, {});
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> c;
                grid[i][j] = c;
                int w = i * m + j;
                if(i != 0) {
                    int v = (i - 1) * m + j, cost = grid[i][j] != grid[i - 1][j];
                    graph[v].push_back({v, w, cost}), graph[w].push_back({w, v, cost});
                }
                if(j != 0) {
                    int v = i * m + j - 1, cost = grid[i][j] != grid[i][j - 1];
                    graph[v].push_back({v, w, cost}), graph[w].push_back({w, v, cost});
                }
            }
        }
        cin >> x >> y >> a >> b;
        dijkstra(x * m + y);
        cout << dist[a * m + b] << endl;
        cin >> n >> m;
    }
}