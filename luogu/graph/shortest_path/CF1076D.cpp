/**
 * @Time : 2025/6/3-17:33
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1076D 1800 图论 最短路 dijkstra
 */
 /*
  * 对最短路径树的理解
  * 在用dijkstra找最短路径的时候 就是在生成一颗最短路径树
  * 每找到一个新的点的最短路径 都是在该树中添加一条边
  * 因此本题中 只能保留k条边 就意味着 只能有k+1个结点在树中（除开起点1就只剩k个结点了）
  * 这就是最大的好结点数量
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, M = 1e6 + 5, mod = 998244353;
ll T, n, m, k;
vector<int> ans;
vector<vector<ll>> graph[N];

vector<ll> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<ll> &a, vector<ll> &b) {
        ll t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int s) {
    vector<bool> marked(n + 1, false);
    priority_queue<vector<ll>, vector<vector<ll>>, cmp> pq;
    distTo = vector(n + 1, LONG_LONG_MAX);
    distTo[s] = 0;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for (auto &edge: graph[v]) {
            ll w = edge[1], weight = edge[2];
            if (distTo[w] > distTo[v] + weight) {
                distTo[w] = distTo[v] + weight;
                pq.push(edge);
            }
        }
    };
    relax(s);
    while (!pq.empty() && ans.size() < k) {
        vector<ll> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]), ans.push_back(edge[3]);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for(int i = 1, v, w, d; i <= m; i++) {
        cin >> v >> w >> d;
        graph[v].push_back({v, w, d, i}), graph[w].push_back({w, v, d, i});
    }
    dijkstra(1);
    cout << ans.size() << "\n";
    for(int id : ans)
        cout << id << " ";
}