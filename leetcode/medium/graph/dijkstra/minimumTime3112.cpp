/**
 * @Time : 2024/4/14-3:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛128 t3
 */
 /*
  * 找到达某个点的最短路径 如果到达该点的最短路 >= 其消失时间 那么该点视为不可达
  * 只需要在dijkstra算法中放缩点的时候 跳过不可达的点即可
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
    vector<int> disappear;
    vector<vector<vector<int>>> graph;
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        this->disappear = disappear;
        graph.assign(n, {});
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1], len = edge[2];
            graph[v].push_back({v, w, len}), graph[w].push_back({w, v, len});
        }
        dijkstra();
        for(int i = 1; i < n; i++)
            if(distTo[i] == INT_MAX) distTo[i] = -1;
        return distTo;
    }

    void dijkstra() {
        int n = graph.size();
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
            int w = edge[1];
            if(distTo[w] >= disappear[w]) distTo[w] = -1;
            if(distTo[w] != -1 && !marked[w])
                relax(w);
        }
    }
};