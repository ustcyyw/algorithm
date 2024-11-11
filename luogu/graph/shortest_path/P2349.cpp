/**
 * @Time : 2023/5/9-12:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 分层图的做法
 * 路程时间加倍前后的点 是不同的点
 */
//#include<bits/stdc++.h>
//
//using namespace std;
//int n, m;
//vector<int> dist;
//vector<bool> marked;
//vector<vector<vector<int>>> graph;
//
//struct cmp{
//    bool operator()(vector<int>& a, vector<int>& b) {
//        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
//        return dist[v1] + c1 >= dist[v2] + c2;
//    }
//};
//
//void dijkstra() {
//    dist = vector(2 * n + 1, INT_MAX);
//    dist[1] = 0;
//    marked = vector(2 * n + 1, false);
//    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
//    function<void(int)> relax = [&](int v) -> void {
//        marked[v] = true;
//        for(auto& edge : graph[v]) {
//            int w = edge[1], c = edge[2];
//            if(dist[w] > dist[v] + c) {
//                dist[w] = dist[v] + c;
//                pq.push(edge);
//            }
//        }
//    };
//    relax(1);
//    while (!pq.empty()) {
//        vector<int> edge = pq.top(); pq.pop();
//        if(!marked[edge[1]])
//            relax(edge[1]);
//    }
//}
//
//int main(){
//    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
//    cin >> n >> m;
//    vector<vector<vector<int>>> edges(256);
//    for(int i = 0, v, w, c; i < m; i++) {
//        cin >> v >> w >> c;
//        edges[c].push_back({v, w, c});
//    }
//    int ans = INT_MAX;
//    for(int time = 3; time <= 255; time++) {
//        if(edges[time].empty()) continue;
//        graph = vector(2 * n + 1, vector(0, vector(0, 0)));
//        for(int i = 3; i <= time; i++) {
//            for(auto& edge : edges[i]) {
//                int v = edge[0], w = edge[1], c = edge[2];
//                graph[v].push_back({v, w, c}), graph[w].push_back({w, v, c});
//                int v2 = v + n, w2 = w + n;
//                graph[v2].push_back({v2, w2, c}), graph[w2].push_back({w2, v2, c});
//            }
//        }
//        for(auto& edge : edges[time]) {
//            int v = edge[0], w = edge[1];
//            int v2 = v + n, w2 = w + n, c2 = 2 * edge[2];
//            graph[v].push_back({v, w2, c2}), graph[w].push_back({w, v2, c2});
//        }
//        dijkstra();
//        ans = min(ans, dist[2 * n]);
//    }
//    cout << ans << endl;
//}

/*
 * 断边的做法
 * 枚举路径中时间加倍的那条边
 */
//#include<bits/stdc++.h>
//
//using namespace std;
//const int max_val = 1e9;
//int n, m;
//vector<int> dist;
//vector<bool> marked;
//vector<vector<vector<int>>> graph;
//
//struct cmp{
//    bool operator()(vector<int>& a, vector<int>& b) {
//        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
//        return dist[v1] + c1 >= dist[v2] + c2;
//    }
//};
//
//vector<int> dijkstra(int dv, int dw, int dc) {
//    dist = vector(n + 1, max_val);
//    dist[dv] = 0;
//    marked = vector(n + 1, false);
//    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
//    function<void(int)> relax = [&](int v) -> void {
//        marked[v] = true;
//        for(auto& edge : graph[v]) {
//            int w = edge[1], c = edge[2];
//            if(c > dc || (v == dv && w == dw) || (v == dw && w == dv)) continue;
//            if(dist[w] > dist[v] + c) {
//                dist[w] = dist[v] + c;
//                pq.push(edge);
//            }
//        }
//    };
//    relax(dv);
//    while (!pq.empty()) {
//        vector<int> edge = pq.top(); pq.pop();
//        if(!marked[edge[1]])
//            relax(edge[1]);
//    }
//    return {dist[1], dist[n]};
//}
//
//int main(){
//    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
//    cin >> n >> m;
//    vector<vector<int>> edges;
//    graph = vector(n + 1, vector(0, vector(0, 0)));
//    for(int i = 0, v, w, c; i < m; i++) {
//        cin >> v >> w >> c;
//        edges.push_back({v, w, c});
//        graph[v].push_back({v, w, c}), graph[w].push_back({w, v, c});
//    }
//    int ans = INT_MAX;
//    for(auto& edge : edges) {
//        int v = edge[0], w = edge[1], c = edge[2];
//        vector<int> t1 = dijkstra(v, w, c), t2 = dijkstra(w, v, c);
//        ans = min(ans, min(t1[0] + t2[1], t1[1] + t2[0]) + 2 * c);
//    }
//    cout << ans << endl;
//}

/*
 * 对dijkstra中最短路径树的重新定义
 * 本题中最长的边会被加倍长度 路径树的距离定义为 路径本身的长度+最大边长度
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
// len[i]从源点到达i的"最短路"上 最长的路径长度
int n, m, max_val = 1e9, dist[N], marked[N], len[N];
vector<vector<vector<int>>> graph;

struct cmp {
    bool operator()(vector<int>& a, vector<int>& b){
        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
        return dist[v1] + c1 + max(c1, len[v1]) >= dist[v2] + c2 + max(c2, len[v2]);
    }
};
void dijkstra(int s){
    fill(dist, dist + n + 1, max_val);
    fill(marked, marked + n + 1, 0);
    fill(len, len + n + 1, 0);
    dist[s] = 0;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for(auto& edge : graph[v]) {
            int w = edge[1], c = edge[2];
            if(dist[w] + len[w] > dist[v] + c + max(c, len[v])) {
                dist[w] = dist[v] + c;
                len[w] = max(c, len[v]);
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
    graph.assign(n + 1, {});
    for(int i = 0, v, w, l; i < m; i++) {
        cin >> v >> w >> l;
        graph[v].push_back({v, w, l}), graph[w].push_back({w, v, l});
    }
    dijkstra(1);
    cout << dist[n] + len[n] << endl;
}