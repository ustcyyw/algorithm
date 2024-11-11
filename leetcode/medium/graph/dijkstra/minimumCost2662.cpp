/**
 * @Time : 2023/5/2-9:57 AM
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
const long t = 1e6;
class Solution {
public:
    /*
     * 本题的关键在于，如果不使用特殊路径，任意亮点直接到达的成本是最小的。
     *
     * 将起点终点，所有特殊路径上的点建图，边权为 abs(x2 - x1) + abs(y2 - y1)，双向
     * 以及特殊路径指定的cost，单向
     */
    vector<vector<vector<int>>> graph;
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        int sx = start[0], sy = start[1], tx = target[0], ty = target[1];
        specialRoads.push_back({sx, sy, tx, ty, distance(sx, sy, tx, ty)});
        int cnt = 0;
        unordered_map<long, int> map;
        for(auto& road : specialRoads) {
            int x1 = road[0], y1 = road[1], x2 = road[2], y2 = road[3];
            long k1 = t * x1 + y1, k2 = t * x2 + y2;
            if(!map.count(k1)) map[k1] = cnt++;
            if(!map.count(k2)) map[k2] = cnt++;
        }
        graph = vector(cnt, vector(0, vector(0, 0)));
        for(auto& p1 : map) {
            int v = p1.second, x1 = p1.first / t, y1 = p1.first % t;
            for(auto& p2 : map) {
                int w = p2.second, x2 = p2.first / t, y2 = p2.first % t;
                if(v == w) continue;
                add(v, w, distance(x1, y1, x2, y2));
            }
        }
        for(auto& road : specialRoads) {
            int x1 = road[0], y1 = road[1], x2 = road[2], y2 = road[3];
            long k1 = t * x1 + y1, k2 = t * x2 + y2;
            int v = map[k1], w = map[k2];
            graph[v].push_back({v, w, road[4]});
        }
        dijkstra(map[sx * t + sy]);
        return distTo[map[tx * t + ty]];
    }

    int distance(int x1, int y1, int x2, int y2){
        return abs(x1 - x2) + abs(y1 - y2);
    }

    void add(int v, int w, int cost) {
        graph[v].push_back({v, w, cost});
        graph[w].push_back({w, v, cost});
    }

    vector<bool> marked;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    void dijkstra(int s){
        int n = graph.size();
        marked = vector(n, false);
        distTo = vector(n, INT_MAX);
        distTo[s] = 0;
        relax(s);
        while (!pq.empty()){
            vector<int> edge = pq.top(); pq.pop();
            if(!marked[edge[1]])
                relax(edge[1]);
        }
    }

    void relax(int v){
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