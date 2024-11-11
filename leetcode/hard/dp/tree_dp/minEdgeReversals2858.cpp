/**
 * @Time : 2023/9/18-5:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 换根dp
 */
class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        vector<vector<vector<int>>> graph(n);
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back({v, w, 1}), graph[w].push_back({w, v, -1});
        }
        vector<int> res(n);
        function<int(int, int)> dfs1 = [&](int v, int f) -> int {
            int res = 0;
            for(auto& edge : graph[v]) {
                int w = edge[1], flag = edge[2];
                if(w == f) continue;
                res += (flag == 1 ? 0 : 1) + dfs1(w, v);
            }
            return res;
        };
        res[0] = dfs1(0, -1);
        function<void(int, int, int)> dfs2 = [&](int v, int f, int flag) -> void {
            if(f != -1) res[v] = res[f] + flag;
            for(auto& edge : graph[v])
                if(edge[1] != f) dfs2(edge[1], v, edge[2]);
        };
        dfs2(0, -1, -1);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}