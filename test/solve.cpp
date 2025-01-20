#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int ansD = 0, cnt = 1;
    vector<int> colors, depth, dis;
    vector<vector<vector<int>>> graph;
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        this->colors = nums;
        graph.assign(n, {});
        for(auto& edge : edges) {
            int a = edge[0], b = edge[1], w = edge[2];
            graph[a].push_back({b, w}), graph[b].push_back({a, w});
        }
        depth.assign(5e4 + 5, 0), dis.assign(5e4 + 5, 0);
        dfs(0, -1, 0, 0);
        return {ansD, cnt};
    }

    void dfs(int v, int f, int layer, int curD) {
        int c = colors[v];
        int dt = curD - dis[c], ct = layer - depth[c];
        if(dt > ansD || (dt == ansD && ct < cnt))
            ansD = dt, cnt = ct;
        for(auto& edge : graph[v]) {
            int w = edge[0], curL = edge[1];
            if(w == f) continue;
            depth[c] = layer, dis[c] = curD + curL;
            dfs(w, v, layer + 1, curD + curL);
        }
    }
};

int main() {
    vector<int> arr1 = {2,2};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
//    vector<vector<int>> arr4 = {{3,0,6},{3,1,6},{2,1,5},{2,4,5}};
    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    s.longestSpecialPath(arr4, arr1);
}
