/**
 * @Time : 2025/7/15-17:38
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3615 状态压缩dp
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string label;
    vector<unordered_set<int>> graph;
    vector<vector<vector<int>>> cache;
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        this->label = label;
        graph.assign(n, {});
        for(vector<int>& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].insert(w), graph[w].insert(v);
        }
        int ans = 1, full = (1 << n) - 1;
        cache = vector(full + 1, vector(n, vector(n, -2)));
        for(int v = 0; v < n && ans != n; v++) {
            for(int w = v + 1; w < n && ans != n; w++) {
                ans = max(ans, dfs(full ^ (1 << v) ^ (1 << w), v, w));
            }
        }
        return ans;
    }

    int dfs(int status, int v1, int v2) {
        if(v1 == v2) return 1;
        if(label[v1] != label[v2]) return -1;
        if(cache[status][v1][v2] != -2) return cache[status][v1][v2];
        int ans = graph[v1].count(v2) ? 2 : -1;
        for(int w1 : graph[v1]) {
            int t1 = 1 << w1;
            if((t1 & status) == 0) continue;
            for(int w2 : graph[v2]) {
                int t2 = 1 << w2;
                if((t2 & status) == 0) continue;
                int temp = dfs(status ^ t1 ^ t2, w1, w2);
                if(temp != -1) ans = max(ans, 2 + temp);
            }
        }
        return cache[status][v1][v2] = ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}