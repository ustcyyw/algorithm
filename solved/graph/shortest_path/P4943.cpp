/**
 * @Time : 2023/5/11-10:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int n, m, k, x, y, dist[N], green[N], marked[N], max_val = 1e9;

struct cmp {
    bool operator()(vector<int>& a, vector<int> b) {
        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
        return dist[v1] + c1 >= dist[v2] + c2;
    }
};

void dijkstra(vector<vector<vector<int>>>& graph, int s) {
    fill(dist, dist + n + 1, max_val);
    memset(marked, 0, sizeof(marked));
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
    while (pq.size()) {
        vector<int> edge = pq.top(); pq.pop();
        if(!marked[edge[1]]) relax(edge[1]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); // 加速cin, cout
    memset(green, 0, sizeof(green));
    cin >> n >> m >> k;
    for (int i = 0, v; i < k; i++) {
        cin >> v;
        green[v] = 1;
    }
    vector<vector<vector<int>>> graph1(n + 1), graph2(n + 1);
    for (int i = 0, v, w, c; i < m; i++) {
        cin >> v >> w >> c;
        graph1[v].push_back({v, w, c}), graph1[w].push_back({w, v, c});
        if (!green[v] && !green[w])
            graph2[v].push_back({v, w, c}), graph2[w].push_back({w, v, c});
    }
    cin >> x >> y;
    int ans = max_val, px1 = -1, py1 = -1, px2 = -1, py2 = -1;
    // 全图走的人从x到y
    dijkstra(graph1, x);
    px1 = dist[1]; // 从0到x的最短路
    ans = min(ans, px1 + dist[y]);
    // 全图走的人从y到x
    dijkstra(graph1, y);
    py1 = dist[1]; // 从0到y的最短路
    ans = min(ans, py1 + dist[x]);
    // 不能进绿房间的人分别去x去y
    dijkstra(graph2, 1);
    px2 = dist[x], py2 = dist[y];
    ans = min({ans, max(px1, py2), max(px2, py1)});
    cout << ans << endl;
}