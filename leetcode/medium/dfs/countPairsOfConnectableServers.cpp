/**
 * @Time : 2024/3/3-3:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛125 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, sp;
    vector<vector<pair<int, int>>> graph;
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int sp) {
        n = edges.size() + 1, this->sp = sp;
        graph.assign(n, {});
        for(auto& edge : edges) {
            int a = edge[0], b = edge[1], w = edge[2];
            graph[a].push_back({b, w}), graph[b].push_back({a, w});
        }
        vector<int> arr;
        for(int i = 0; i < n; i++) {
            int res = 0, sum = 0;
            for(auto& p : graph[i]) {
                int cnt = dfs(p.first, i, p.second);
                res += sum * cnt, sum += cnt;
            }
            arr.push_back(res);
        }
        return arr;
    }

    int dfs(int v, int f, int dis) {
        int cnt = dis % sp == 0;
        for(auto& p : graph[v]) {
            if(p.first == f) continue;
            cnt += dfs(p.first, v, dis + p.second);
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}