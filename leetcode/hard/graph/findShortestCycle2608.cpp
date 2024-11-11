/**
 * @Time : 2023/4/5-9:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 环的一种理解：从一个点出发，有两条简单路径可以到达另外一个点
     *
     * 枚举边：枚举某一条边 v-w，从图中删除这条边
     * 然后从v出发，如果还能到达w，就说明v-w这条边在环中
     * 从v出发使用bfs找到的就是最短路
     *
     * 枚举点：从某个点v出发访问别的点，可能会经过不同的路径走到同一个点
     * 才用bfs进行访问，两条路径就是到达该点的最短，次短路径，这就构成了一个可能的最短环
     * 环的长度等于两路径长度之和再+1
     * 如果出现 1 -> 2 -> 3 -> 4
     * 和 1 -> 2 -> 3 -> 5
     * 并且4和5有一条边相连的情况，计算出环的长度是7 但是3 4 5这个环，长度是3
     * 这种不正确的情况环长 > 正确的情况，因此正确答案在枚举3这个结点的时候取得，覆盖了错误答案
     * 不用担心错误情况的出现
     */

    // 枚举点的做法
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        int res = INT_MAX;
        for(int v = 0; v < n; v++)
            res = min(res, min_cycle(graph, n, v));
        return res == INT_MAX ? -1 : res;
    }

    int min_cycle(vector<vector<int>>& graph, int n, int s){
        vector<int> dis(n, -1), father(n, -1);
        dis[s] = 0;
        queue<int> queue;
        queue.push(s);
        int step = 0, res = INT_MAX;
        while (!queue.empty()){
            int sz = queue.size();
            for(int i = 0; i < sz; i++){
                int v = queue.front(); queue.pop();
                for(int w : graph[v]){
                    if(father[v] == w) continue; // w是v的父亲 跳过
                    if(dis[w] == -1) {
                        dis[w] = step + 1;
                        father[w] = v;
                        queue.push(w);
                    } else res = min(res, step + dis[w] + 1); // step：到达v的路径长，dis[w]到达w的路径长
                }
            }
            step++;
        }
        return res;
    }

    // 删边，枚举边的做法
    int findShortestCycle2(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        int res = INT_MAX;
        for(auto& edge : edges)
            res = min(res, min_cycle(graph, n, edge[0], edge[1]));
        return res == INT_MAX ? -1 : res;
    }

    int min_cycle(vector<vector<int>>& graph, int n, int s, int t){
        vector<bool> marked(n, false);
        marked[s] = true;
        queue<int> queue;
        queue.push(s);
        int step = 0, res = INT_MAX;
        while (!queue.empty()){
            int sz = queue.size();
            for(int i = 0; i < sz; i++){
                int v = queue.front(); queue.pop();
                for(int w : graph[v]){
                    if((v == s && w == t) || marked[w]) continue; // v-w 这条边被删除
                    // step是到达v的距离，+1是到达w的距离，环的距离还要再加上 v-w 这条被删的边
                    if(w == t) return step + 2;
                    queue.push(w);
                    marked[w] = true;
                }
            }
            step++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}