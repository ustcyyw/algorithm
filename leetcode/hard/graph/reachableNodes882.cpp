/**
 * @Time : 2023/3/28-11:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

vector<int> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        int t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};

class Solution {
public:
    vector<bool> marked;
    vector<vector<vector<int>>> graph;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        distTo = vector(n, INT_MAX);
        marked = vector(n, false);
        graph.assign(n, {});
        for(auto& edge : edges){
            int v = edge[0], w = edge[1], weight = edge[2] + 1;
            graph[v].push_back({v, w, weight}), graph[w].push_back({w, v, weight});
        }
        distTo[0] = 0;
        relax(graph, 0);
        while (!pq.empty()){
            vector<int> edge = pq.top(); pq.pop();
            // 到达edge[1]这个点的距离超过maxMoves，则这个点不必再添加到最短路径树中
            if(!marked[edge[1]] && distTo[edge[1]] <= maxMoves)
                relax(graph, edge[1]);
        }
        int res = 0;
        for(int v = 0; v < n; v++) // 可达的点计数
            if(distTo[v] <= maxMoves) res++;
        for(auto& edge : edges){
            int v = edge[0], w = edge[1], cnt = edge[2];
            int t = 0; // 表示从v，w往这条边里面走 还能走多少条边的和
            // 如果可以到达v，还剩余的距离为 maxMoves - distTo[v]
            if(distTo[v] <= maxMoves) t += maxMoves - distTo[v];
            if(distTo[w] <= maxMoves) t += maxMoves - distTo[w];
            res += min(t, cnt);
        }
        return res;
    }

    void relax(vector<vector<vector<int>>>& graph, int v){
        marked[v] = true;
        for(auto& edge : graph[v]){
            int w = edge[1], weight = edge[2];
            if(distTo[w] > distTo[v] + weight){
                distTo[w] = distTo[v] + weight;
                pq.push(edge);
            }
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}