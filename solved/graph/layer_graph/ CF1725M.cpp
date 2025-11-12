/**
 * @Time : 2024/7/10-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1725M 分层图 最短路
 */
/*
 * 对于f(i)，要找的答案是 min{dis(1,j) + dis(i,j)}
 * 如果建立反图 dis(i,j) = r_dis(j,i)
 * min{dis(1,j) + r_dis(j,i)}
 * 一个是原图中的最短距离，一个是反图中的最短距离 如何将二者建立联系
 * 可以建分层图 将原图视为第一层，反图视为第二层 r_j = j + n
 * min{dis(1,j) + r_dis(j,i)}
 * = min(dis(1,j) + dis(j, r_j) + dis(r_j, r_i))
 * 其中 dis(j, r_j) = 0， 这是j -> r_j的权重为0的边
 *
 * 特殊地 如果 f(i)答案的那个点就是i
 * 也可以理解为这个距离是 dis(1,i) + dis(i, r_i) 也是从1到r_i点
*/
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, marked[N];
ll distTo[N];
vector<vector<int>> graph[N];

struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        ll t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};

void solve() {
    fill(distTo, distTo + 2 * n + 2, LONG_LONG_MAX);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    distTo[1] = 0;
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
    relax(1);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
    for(int i = 2; i <= n; i++)
        cout << (distTo[i + n] == LONG_LONG_MAX ? -1 : distTo[i + n]) << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        graph[i].push_back({i, i + n, 0});
    for(int i = 1, a, b, d; i <= m; i++) {
        cin >> a >> b >> d;
        graph[a].push_back({a, b, d});
        graph[b + n].push_back({b + n, a + n, d});
    }
    solve();
};