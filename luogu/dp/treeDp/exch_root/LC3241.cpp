/**
 * @Time : 2025/1/16-11:40 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3241 动态规划 换根dp
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> time, d1, d2, node1;
    vector<vector<int>> graph;
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        graph.assign(n, {});
        time.assign(n, 0), d1.assign(n, 0), d2.assign(n, 0), node1.assign(n, -1);
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(0, -1);
        dfs2(0, -1, 0);
        return time;
    }

    void dfs1(int v, int f) {
        for(int w : graph[v]) {
            if(w == f) continue;
            dfs1(w, v);
            int add = w % 2 == 1 ? 1 : 2, t = add + d1[w];
            if(t >= d1[v]) {
                d2[v] = d1[v];
                d1[v] = t, node1[v] = w;
            } else if(t > d2[v]) d2[v] = t;
        }
    }

    void dfs2(int v, int f, int d) {
        time[v] = max(d, d1[v]);
        for(int w : graph[v]) {
            if(w == f) continue;
            int add = v % 2 == 1 ? 1 : 2;
            int dis = node1[v] == w ? d2[v] : d1[v];
            dfs2(w, v, max(dis, d) + add);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}