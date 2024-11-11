/**
 * @Time : 2024/4/28-10:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛394 t4 最短路dijkstra
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4 + 5;
int distTo[N], marked[N];
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        int t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
class Solution {
public:
    vector<vector<int>> edges;
    vector<vector<int>> in;
    vector<bool> ans;
    void dijkstra(vector<vector<vector<int>>>& graph, int s) {
        int n = graph.size();
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
        fill(distTo, distTo + n + 1, INT_MAX);
        memset(marked, 0, sizeof(marked));
        distTo[s] = 0;
        in.assign(n, {}); // 存放到达w的最短路径上的边的编号
        function<void(int)> relax = [&](int v) {
            marked[v] = true;
            for (auto &edge: graph[v]) {
                int w = edge[1], weight = edge[2], id = edge[3];
                if (distTo[w] > distTo[v] + weight) {
                    distTo[w] = distTo[v] + weight;
                    in[w].clear();
                    pq.push(edge);
                }
                if(distTo[w] == distTo[v] + weight)
                    in[w].push_back(id);
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

    void path(int x) {
        if(x == 0 || marked[x]) return;
        marked[x] = 1;
        for(int id : in[x]) {
            vector<int>& edge = edges[id];
            int w = edge[0] == x ? edge[1] : edge[0];
            ans[id] = true;
            path(w);
        }
    }

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        this->edges = edges;
        vector<vector<vector<int>>> graph(n);
        ans = vector(edges.size(), false);
        for(int i = 0; i < edges.size(); i++) {
            vector<int>& edge = edges[i];
            int v = edge[0], w = edge[1], len = edge[2];
            graph[v].push_back({v, w, len, i}), graph[w].push_back({w, v, len, i});
        }
        dijkstra(graph, 0);
        memset(marked, 0, sizeof(marked));
        path(n - 1);
        return ans;
    }
};