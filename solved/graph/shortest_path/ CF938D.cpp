/**
 * @Time : 2024/5/22-11:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF938D 最短路 dijkstra 超级源点
 */
/*
 * 在图论中常见的 超级源点的套路
 * 假设超级源点编号为0 这个结点到其它结点i的路径长度为a[i]
 * 其它结点相互之间的权重为2*w：表示走这条路来回的代价
 * 那么从超级源点为起点找最短路径树 对于点i
 * 1.就是从0到i的这条边，就表示i点看演唱会 就是在自己这个点 花费为a[i]
 * 2.从0先到达某个点j，再由j走其它路到i
 * 那么花费就是a[j] + 路程花费，就表示i这个点看演唱会 走到j去看最好
 * 以上就涵盖了i点看演唱会所有可能的决策 因此找最短路就找到了看演唱会的最小花费
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, m, distTo[N], marked[N];
vector<vector<ll>> graph[N];
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<ll> &a, vector<ll> &b) {
        ll t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int s) {
    priority_queue<vector<ll>, vector<vector<ll>>, cmp> pq;
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
    while (!pq.empty()) {
        vector<ll> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

void solve() {
    fill(distTo, distTo + n + 2, LONG_LONG_MAX);
    dijkstra(0);
    for(int i = 1; i <= n; i++)
        cout << distTo[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(ll i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({a, b, 2 * w}), graph[b].push_back({b, a, 2 * w});
    }
    for(ll i = 1, val; i <= n; i++) {
        cin >> val;
        graph[0].push_back({0, i, val});
    }
    solve();
};