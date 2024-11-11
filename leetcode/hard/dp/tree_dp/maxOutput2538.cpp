/**
 * @Time : 2023/3/27-8:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int res = -1;
    vector<int> points, price;
    vector<vector<int>> graph;
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        this->price = price;
        points = vector(n, -1);
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(0, -1); // 固定一个根结点，进行第一次递归
        dfs2(0, -1, 0);
        return res;
    }
    // 递归得到以v为根的最大路径价值，存放在points[v]中
    void dfs1(int v, int father){
        int point = 0;
        for(int w : graph[v]){
            if(w == father) continue;
            dfs1(w, v);
            point = max(point, points[w]);
        }
        points[v] = point + price[v];
    }
    // p3表示从father经过v的路径且不包含v的最大路径价值
    void dfs2(int v, int father, int p3){
        int p1 = -1, p2 = -1;
        for (int w: graph[v]) {
            if (w == father) continue;
            if (p1 <= points[w])
                p2 = p1, p1 = points[w];
            else p2 = max(p2, points[w]);
        }
        int p = max(p3, p1);
        res = max(res, p);
        for(int w : graph[v]) {
            if (w == father) continue;
            p = p1 == points[w] ? max(p3, p2) : max(p3, p1);
            dfs2(w, v, p + price[v]);
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> arr = {{0,1},{1,2}};
    vector<int> price = {1,1,1};
    s.maxOutput(3, arr, price);
    cout << 0 << endl;
}