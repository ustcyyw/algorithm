/**
 * @Time : 2025/1/8-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3286 图论 最短路 dijkstra
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 128;
int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};

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
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>> graph(n * m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int v = i * m + j;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if(nx < 0 || ny < 0 || nx == n || ny == m) continue;
                    graph[v].push_back({v, nx * m + ny, grid[nx][ny]});
                }
            }
        }
        if(grid[0][0] == 1) health--;
        dijkstra(graph, 0);
        return distTo[n * m - 1] < health;
    }

    void dijkstra(vector<vector<vector<int>>> graph, int s) {
        int n = graph.size();
        vector<bool> marked(n, false);
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
        distTo = vector(n, INT_MAX);
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
};