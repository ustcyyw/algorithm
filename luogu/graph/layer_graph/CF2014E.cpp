/**
 * @Time : 2024/10/12-10:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2014E 分层图 dijkstra
 */
/*
  * 分层图 因为显然路径权值有两类 并且从第一类可以转换到第二类
  * 有马的点可以以0的权值到达第二层的点 第二层的点之间权值为原本的一半
  * 先求最短路 然后再枚举汇合地点即可
  *
  * 会不会有两个人在同一个点都骑马导致算错的情况
  * 不会，因为如果两个人都在同一个骑马了 那他们直接不走就已经遇到了 省去骑马后的时间更快
  * 所以压根不用考虑这个情况
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, h;
vector<vector<vector<int>>> graph;

vector<ll> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        ll t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int s) {
    int n = graph.size();
    vector<bool> marked(n, false);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    distTo = vector(n, (ll)1e15);
    distTo[s] = 0;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for (auto &edge: graph[v]) {
            int w = edge[1], weight = edge[2];
            if (distTo[w] > distTo[v] + weight) {
                distTo[w] = distTo[v] + weight;
                pq.push(edge);
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

void solve() {
    dijkstra(1);
    vector<ll> dt = distTo;
    dijkstra(n);
    ll ans = LONG_LONG_MAX;
    for(int i = 1; i <= n; i++) {
        ll t1 = max(dt[i], distTo[i]), t2 = max(dt[i], distTo[i + n]);
        ll t3 = max(dt[i + n], distTo[i]), t4 = max(dt[i + n], distTo[i + n]);
        ans = min({ans, t1, t2, t3, t4});
    }
    if(ans >= (ll)1e15) ans = -1;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> h;
        graph.assign(2 * (n + 5), {});
        for(int i = 1, a; i <= h; i++) {
            cin >> a;
            graph[a].push_back({a, a + n, 0});
        }
        for(int i = 1, v, w, time; i <= m; i++) {
            cin >> v >> w >> time;
            graph[v].push_back({v, w, time}); graph[w].push_back({w, v, time});
            graph[v + n].push_back({v + n, w + n, time / 2});
            graph[w + n].push_back({w + n, v + n, time / 2});
        }
        solve();
    }
};