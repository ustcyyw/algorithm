/**
 * @Time : 2025/11/4-12:37
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3650 1853 图论 dijkstra 思维
 */
#include<bits/stdc++.h>
using namespace std;

vector<int> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        int t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};

class Solution {
public:
    vector<vector<vector<int>>> graph;
    int minCost(int n, vector<vector<int>>& edges) {
        graph.assign(n, {});
        for(auto& edge : edges) {
            int a = edge[0], b = edge[1], w = edge[2];
            graph[a].push_back(edge), graph[b].push_back({b, a, 2 * w});
        }
        vector<bool> marked(n, false);
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
        distTo = vector(n, INT_MAX);
        distTo[0] = 0;
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
        relax(0);
        while (!pq.empty()) {
            vector<int> edge = pq.top();
            pq.pop();
            if (!marked[edge[1]])
                relax(edge[1]);
        }
        return distTo[n - 1] == INT_MAX ? -1 : distTo[n - 1];
    }
};
