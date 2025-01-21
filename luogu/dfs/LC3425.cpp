/**
 * @Time : 2025/1/20-9:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3425 dfs 前缀和思想
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ansD = 0, cnt = 1;
    vector<int> colors;
    // 模拟递归栈中对应颜色的深度、某个深度对应的距离前缀
    unordered_map<int, vector<int>> layer, dis;
    vector<vector<vector<int>>> graph;
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        this->colors = nums;
        graph.assign(n, {});
        for(auto& edge : edges) {
            int a = edge[0], b = edge[1], w = edge[2];
            graph[a].push_back({b, w}), graph[b].push_back({a, w});
        }
        dfs(0, -1, 0, 0, 0);
        return {ansD, cnt};
    }
    // pre表示结点向上最多能走到第几层而没有重复颜色的结点
    void dfs(int v, int f, int curL, int curD, int pre) {
        int c = colors[v];
        int sameL = (!layer.count(c) || layer[c].empty()) ? -1 : layer[c].back();
        pre = max(pre, sameL + 1);
        layer[c].push_back(curL), dis[curL].push_back(curD);
        int dt = curD - dis[pre].back(), ct = curL - pre + 1;
        if(dt > ansD || (dt == ansD && ct < cnt))
            ansD = dt, cnt = ct;
        for(auto& edge : graph[v]) {
            int w = edge[0], d = edge[1];
            if(w == f) continue;
            dfs(w, v, curL + 1, curD + d, pre);
        }
        layer[c].pop_back(), dis[curL].pop_back();
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}