/**
 * @Time : 2023/11/11-4:24 PM
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
* 可能会出现无论如何调整都没法使最短路径长度(记为min_len)变为target的情况
* 1.如果不使用任何待调整边 min_len 就已经小于target了
* 那么无论把待调整边设置为多少，都是增加了更多选择
* 有更多选择的情况下 min_len 要么不变 要么更小 总之就是小于target
* 2.如果将待调整边全设置为最小值1，计算出来的min_len是最小的
* 如果还有 min_len > target 那就无法调整了
*
* 其余情况都可以完成调整 在通过上述验证的情况下
* 不使用待调整边 根据情况1可知 min_len >= target
* 如果已经有min_len == target，那么直接将所有待调整边的长度变为正无穷 保证不会经过这些边 就能维持结果
* 否则 调整这些边。那么 要使min_len == target，说明最短路径是要经过这些边的
*
* 可以尝试遍历调整的边 记dis[s][dest]是起点到终点的最短路径长度长度
* 将当前这条边调整为1 算出调整后的dis[s][dest] 如果有 dis[s][dest] <= target
* 说明经过这条边到达dest的最短路径长度 <= target了
* 因为不调整这条边之前source到dest的最短路径长度 > target
* 那出现这样的情况 只能是最短路径经过当前边了
* 那么我们将当前这条边的长度设置为 target - dis[s][dest] + 1
* (要使最短路径长度为target，此条变长还要再加上target - dis[s][dest]，
* 原本是以其长度为1参与计算，于是其长度设置为target - dis[s][dest] + 1)
* 并且令其它待调整边的长度为正无穷，就不影响这一条最短路
* 如果 dis[s][dest] > target 说明即便将这条路径设置为1，也还不能使最短路径长度 <= target
* 那么将其设置为更大的值 更不可能满足条件
* 于是将其设置为1 以便再继续调整下一条边时 更大可能地出现dis[s][dest] <= target
*/
    // 超时 暴力算法
//    int n;
//    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int dest, int target) {
//        this-> n = n;
//        vector<vector<int>> grid(n, vector(n, INT_MAX));
//        for(auto& edge : edges) {
//            int a = edge[0], b = edge[1], w = edge[2];
//            if(w != -1) grid[a][b] = grid[b][a] = w;
//        }
//        // 检查是否可以调整的第一类情况
//        vector<long long> dist1 = dijkstra(grid, source);
//        if(dist1[dest] < target) return {};
//        if(dist1[dest] == target) { // 特殊地 如果最短路已经是target的长度了，就调整这些边全为正无穷 不影响这条路径即可
//            for(auto& edge : edges)
//                if(edge[2] == -1) edge[2] = max_val;
//            return edges;
//        }
//        for(auto& edge : edges) {
//            int a = edge[0], b = edge[1], w = edge[2];
//            if(w != -1) continue;
//            grid[a][b] = grid[b][a] = 1;
//            vector<long long> dist2 = dijkstra(grid, source);
//            if(dist2[dest] <= target) {
//                edge[2] = target - dist2[dest] + 1;
//                for(auto& e : edges) {
//                    if(e[2] == -1) e[2] = max_val;
//                }
//                return edges;
//            }
//            edge[2] = 1;
//        }
//        return {}; // 对应第二种情况，所有可调整的边变为1 最短路径还是大于target
//    }
//
//    vector<long long> dijkstra(vector<vector<int>>& grid, int s) {
//        vector<long long> dist(n, max_val);
//        vector<bool> marked(n, false);
//        dist[s] = 0;
//        for(int i = 0; i < n; i++) { // 每次将一个点添加到最短路径树中 共添加n个点
//            long long val = max_val, v = -1;
//            for(int j = 0; j < n; j++) { // 找到当前距离最小的点 就是这一轮添加到最短路径树中的点
//                if(marked[j]) continue;
//                val = min(val, dist[j]);
//                if(dist[j] == val) v = j;
//            }
//            marked[v] = true;
//            for(int w = 0; w < n; w++) { // 放缩
//                if(!marked[w] && dist[w] > dist[v] + grid[v][w])
//                    dist[w] = dist[v] + grid[v][w];
//            }
//        }
//        return dist;
//    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}