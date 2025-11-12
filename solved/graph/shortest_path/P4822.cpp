/**
 * @Time : 2023/5/9-5:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 分层图 跑dijkstra
 */
#include<bits/stdc++.h>

using namespace std;
int n, m, k;
vector<int> dist;
vector<bool> marked;
vector<vector<vector<int>>> graph;

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b) {
        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
        return dist[v1] + c1 >= dist[v2] + c2;
    }
};

void dijkstra() {
    dist = vector((k + 1) * n + 1, INT_MAX);
    dist[1] = 0;
    marked = vector((k + 1) * n + 1, false);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    function<void(int)> relax = [&](int v) -> void {
        marked[v] = true;
        for(auto& edge : graph[v]) {
            int w = edge[1], c = edge[2];
            if(dist[w] > dist[v] + c) {
                dist[w] = dist[v] + c;
                pq.push(edge);
            }
        }
    };
    relax(1);
    while (!pq.empty()) {
        vector<int> edge = pq.top(); pq.pop();
        if(!marked[edge[1]])
            relax(edge[1]);
    }
}

void add(int v, int w, int c) {
    graph[v].push_back({v, w, c}), graph[w].push_back({w, v, c});
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    graph.assign((k + 1) * n + 1, {});
    for(int i = 0, v, w, c; i < m; i++) {
        cin >> v >> w >> c;
        add(v, w, c);
        for(int half = c / 2, j = 1, pv = v, pw = w; j <= k; j++) {
            int nv = v + n * j, nw = w + n * j;
            add(nv, nw, c);
            graph[pv].push_back({pv, nw, half});
            graph[pw].push_back({pw, nv, half});
            pv = nv, pw = nw;
        }
    }
    int ans = INT_MAX;
    dijkstra();
    for(int i = 0; i <= k; i++)
        ans = min(dist[n * (i + 1)], ans);
    cout << ans << endl;
}