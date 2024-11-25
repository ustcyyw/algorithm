/**
 * @Time : 2024/11/24-10:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<vector<int>>> graph;
        graph.assign(n, {});
        vector<vector<ll>> cache(n + 1, vector(2, -1ll));
        for(auto edge : edges) {
            int v = edge[0], w = edge[1], c = edge[2];
            graph[v].push_back({v, w, c}), graph[w].push_back({w, v, c});
        }
        // flag = 0表示要去掉f和v之间的边
        function<ll(int, int, int)> dfs = [&](int v, int f, int flag) -> ll{
            if(graph[v].size() == 1 && f != -1) return 0;
            if(cache[v][flag] != -1) return cache[v][flag];
            long ans = 0, cnt = flag;
            priority_queue<ll> aux;
            for(auto edge : graph[v]) {
                int w = edge[1], c = edge[2];
                if(w == f) continue;
                long t1 = dfs(w, v, 0), t2 = dfs(w, v, 1) + c;
                if(t1 >= t2) ans += t1;
                else ans += t2, cnt++, aux.push(t1 - t2);
            }
            while(cnt > k) {
                ans += aux.top();
                aux.pop(), cnt--;
            }
            return cache[v][flag] = ans;
        };
        return dfs(0, -1, 0);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}