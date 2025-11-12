/**
 * @Time : 2024/12/10-10:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1915G 1800 图论 分层图 dijkstra
 */
/*
  * 结点最多1000个 可用的速度最多1000个
  * 可以将(结点,速度)的二维组合视为虚拟结点
  * 从(v,j)出发可以到达的虚拟结点(w,j)，其中v-w是一条存在的原始边，这条虚拟边长为 len(v,w) * s[j]
  * 到达任何一个结点虚拟都可以换成该位置的速度 比如在(w,j)通过边长为0的边到达(w,w)
  * 于是跑最短路的时候 记录访问状态，记录虚拟结点都使用二维进行记录
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//const int N = 2e5 + 5;
int T, n, m, s[1005];
vector<vector<vector<int>>> graph;

vector<vector<ll>> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        ll t = distTo[a[0]][a[3]] + a[2] * s[a[3]] - distTo[b[0]][b[3]] - b[2] * s[b[3]];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
ll dijkstra() {
    vector<vector<bool>> marked(n + 1, vector(n + 1, false));
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    distTo = vector(n + 1, vector(n + 1, LONG_LONG_MAX));
    distTo[1][1] = 0;
    function<void(int, int)> relax = [&](int v, int j) {
        marked[v][j] = true;
        for (auto &edge: graph[v]) {
            int w = edge[1], weight = edge[2];
            if (distTo[w][j] > distTo[v][j] + weight * s[j]) {
                distTo[w][j] = distTo[v][j] + weight * s[j];
                pq.push({edge[0], w, weight, j});
            }
        }
    };
    relax(1, 1);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        int w = edge[1], j = edge[3];
        if(w == n) return distTo[w][j];
        pq.pop();
        if (!marked[w][j])
            relax(w, j);
        if(!marked[w][w]) { // 到达w点后 查看是否以w点的速度行走过。
            // 最快到达w的时间是 distTo[w][j]，在w点换车不消耗时间，因此到达(w,w)的最短时间就是它
            // 然后对(w,w)点放缩
            distTo[w][w] = distTo[w][j];
            relax(w, w);
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {});
        for(int i = 1, a, b, w; i <= m; i++) {
            cin >> a >> b >> w;
            graph[a].push_back({a, b, w}), graph[b].push_back({b, a, w});
        }
        for(int i = 1; i <= n; i++)
            cin >> s[i];
        cout << dijkstra() << "\n";
    }
};