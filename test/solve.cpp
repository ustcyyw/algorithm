#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

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

int main() {
    vector<int> arr1 = {8, 10, 9};
    vector<int> arr2 = {10, 6, 6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
    s.maxLen(3, arr4, "aaa");
}
