/**
 * @Time : 2024/7/15-10:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1846G dijkstra
 */
 /*
  * 将生病的状态当作结点 吃某种药可以从某种状态变为另外一种状态 视为边长为d
  * 构建有向图 跑最短路
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1000 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, d[N], s[N], f[N], start, full, distTo[1100];
string t1, t2;
vector<vector<vector<int>>> graph;

int to_status(string& t) {
    int status = 0;
    for(int i = 0; i < t.size(); i++) {
        if(t[i] == '1')
            status |= (1 << i);
    }
    return status;
}

void build() {
    graph.assign(full, {});
    for(int u = 0; u < full; u++) {
        for(int i = 1; i <= m; i++) {
            int nu = ((u & s[i]) ^ u) | f[i];
            graph[u].push_back({u, nu, d[i]});
        }
    }
}

struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        int t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int st) {
    int n = graph.size();
    vector<bool> marked(n, false);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    distTo[st] = 0;
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
    relax(st);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

void solve() {
    build();
    dijkstra(start);
    cout << (distTo[0] == INT_MAX ? -1 : distTo[0]) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        full = 1 << n;
        fill(distTo, distTo + full + 1, INT_MAX);
        cin >> t1;
        start = to_status(t1);
        for(int i = 1; i <= m; i++) {
            cin >> d[i] >> t1 >> t2;
            s[i] = to_status(t1), f[i] = to_status(t2);
        }
        solve();
    }
};