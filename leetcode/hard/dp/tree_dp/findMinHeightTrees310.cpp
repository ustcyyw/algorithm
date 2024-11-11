/**
 * @Time : 2023/3/27-8:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int min_h;
    vector<int> height, res;
    vector<vector<int>> graph;
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        height = vector(n, 0);
        graph = vector(n, vector(0, 0));
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        min_h = dfs1(0, -1);
        dfs2(0, -1, 0);
        return res;
    }

    int dfs1(int v, int father){
        int h = 0;
        for(int w : graph[v]){
            if(w == father) continue;
            h = max(h, dfs1(w, v) + 1);
        }
        height[v] = h;
        return h;
    }
    // d3是从father到v到最长路径长度
    void dfs2(int v, int father, int d3){
        int d1 = -1, d2 = -1;
        for(int w : graph[v]){
            if(w == father) continue;
            if(height[w] + 1 >= d1) d2 = d1, d1 = height[w] + 1;
            else d2 = max(d2, height[w] + 1);
        }
        int d = max(d1, d3);
        if(d < min_h) {
            min_h = d;
            res.clear();
        }
        if(d == min_h) res.push_back(v);
        for(int w : graph[v]) {
            if (w == father) continue;
            d = (d1 == height[w] + 1 ? max(d3, d2) : max(d1, d3)) + 1;
            dfs2(w, v, d);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}