/**
 * @Time : 2023/3/28-10:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
/*
 * 堆优化 时间复杂度mlogn
 */
vector<int> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        int t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
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

/*
 * 朴素版本 用邻接矩阵存图 时间复杂度n*n
 * 结点编号从0开始
 */
const int N = 105, max_val = 1e9;
int n, dist[N], path[N], marked[N], grid[N][N];

void dijkstra2(int s) {
    fill(dist, dist + n + 1, max_val);
    fill(path, path + n + 1, -1);
    fill(marked, marked + n + 1, 0);
    dist[s] = 0;
    for(int i = 0; i < n; i++) { // 每次将一个点添加到最短路径树中 共添加n个点
        int val = max_val, v = -1;
        for(int j = 0; j < n; j++) { // 找到当前距离最小的点 就是这一轮添加到最短路径树中的点
            if(marked[j]) continue;
            val = min(val, dist[j]);
            if(dist[j] == val) v = j;
        }
        marked[v] = true;
        for(int w = 0; w < n; w++) { // 放缩
            if(!marked[w] && dist[w] > dist[v] + grid[v][w]) {
                dist[w] = dist[v] + grid[v][w];
                path[w] = v;
            }
        }
    }
}

vector<int> get_path(int e) {
    vector<int> ans;
    while (e != -1) {
        ans.push_back(e);
        e = path[e];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}