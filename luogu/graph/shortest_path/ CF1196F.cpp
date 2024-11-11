/**
 * @Time : 2024/5/16-4:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1196F dijkstra 减枝
 */
 /*
  * 注意到k <= 400。那么最短的第k条路径长度 <= 第k短的边 <= 第400短的边
  * 因此这个图中有效的边最多400条 可以暴力枚举起点使用dijkstra
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e6;
int n, m, k;
vector<vector<int>> edges, graph[N];

unordered_map<int, ll> distTo;
unordered_set<int> marked;
unordered_set<ll> inPaths;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        ll t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

struct cmp1 {
    bool operator()(vector<ll> &a, vector<ll> &b) {
        return a[0] < b[0]; // cpp 中优先队列是大顶堆
    }
};
priority_queue<vector<ll>, vector<vector<ll>>, cmp1> paths;

// 将v添加到最短路径树中
void add(int s, int v) {
    marked.insert(v);
    if(s == v) return;
    int a = min(s, v), b = max(s, v);
    ll key = (ll)a * T + b;
    if(inPaths.count(key)) return;
    inPaths.insert(key);
    paths.push({distTo[v], key});
    if(paths.size() > k) {
        inPaths.erase(inPaths.find(paths.top()[1]));
        paths.pop();
    }
}

void relax(int s, int v) {
    // 将v添加到最短路径树中
    add(s, v);
    for (auto &edge: graph[v]) {
        int w = edge[1], weight = edge[2];
        if (!distTo.count(w) || distTo[w] > distTo[v] + weight) {
            distTo[w] = distTo[v] + weight;
            if(paths.size() < k || distTo[w] <= paths.top()[0])
                pq.push(edge);
        }
    }
}

void dijkstra(int s) {
    pq = {}, marked.clear(), distTo.clear();
    distTo[s] = 0;
    relax(s, s);
    while (!pq.empty() && marked.size() <= k + 1) {
        vector<int> edge = pq.top();
        if(paths.size() >= k && distTo[edge[1]] >= paths.top()[0])
            break;
        pq.pop();
        if (!marked.count(edge[1]))
            relax(s, edge[1]);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        edges.push_back({w, a, b});
    }
    sort(edges.begin(), edges.end());
    for(int i = 0; i < min(k, m); i++) {
        vector<int>& edge = edges[i];
        int a = edge[1], b = edge[2], w = edge[0];
        graph[a].push_back({a, b, w}), graph[b].push_back({b, a, w});
    }
    // 枚举源点
    for(int i = 1; i <= n; i++)
        dijkstra(i);
    cout << paths.top()[0];
};