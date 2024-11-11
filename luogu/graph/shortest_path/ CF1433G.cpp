/**
 * @Time : 2024/7/5-10:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1433G 图论 最短路 dijkstra 动态加边
 */
/*
  * 先用dijkstra将所有的dis[i][j]算出来
  * 然后参考floyd算法中的动态加边 dis[i][j] = min(dis[i][j], dis[i][v] + cost[v,w] + dis[w][j])
  * 可以枚举权重要改为0的边 其 cost = 0 但注意这里是无向图 所以正确的两点间距离为
  * dis[i][j] = min(dis[i][j], dis[i][v] + dis[w][j], dis[i][w] + dis[v][j])
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1005, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k, marked[N], distTo[N][N], points[N][2], edges[N][2];
vector<vector<int>> graph[N];

// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        ll t = distTo[a[3]][a[0]] + a[2] - distTo[a[3]][b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int s) {
    memset(marked, 0, sizeof(marked));
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    for(int i = 1;i <= n; i++)
        distTo[s][i] = INT_MAX;
    distTo[s][s] = 0;
    function<void(int)> relax = [&](int v) {
        marked[v] = 1;
        for (auto &edge: graph[v]) {
            int w = edge[1], weight = edge[2];
            if (distTo[s][w] > distTo[s][v] + weight) {
                distTo[s][w] = distTo[s][v] + weight;
                pq.push({edge[0], w, weight, s});
            }
        }
    };
    relax(s);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

int cal(int v, int w) {
    int sum = 0;
    for(int i = 1; i <= k; i++) {
        int a = points[i][0], b = points[i][1];
        sum += min({distTo[a][b], distTo[a][v] + distTo[w][b], distTo[a][w] + distTo[v][b]});
    }
    return sum;
}

void solve() {
    for(int i = 1; i <= n; i++)
        dijkstra(i);
    int ans = INT_MAX;
    for(int i = 1; i <= m; i++)
        ans = min(ans, cal(edges[i][0], edges[i][1]));
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        edges[i][0] = a, edges[i][1] = b;
        graph[a].push_back({a, b, w}), graph[b].push_back({b, a, w});
    }
    for(int i = 1; i <= k; i++)
        cin >> points[i][0] >> points[i][1];
    solve();
};