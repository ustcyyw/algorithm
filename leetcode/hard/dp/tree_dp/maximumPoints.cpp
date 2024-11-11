/**
 * @Time : 2023/10/29-12:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛369 t4
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        int n = coins.size();
        vector<vector<int>> graph(n);
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        vector<vector<int>> cache(n, vector(15, -1));
        function<long long(int, int, int)> dfs = [&](int v, int f, int cnt) -> long long {
            if(cnt >= 14) return 0;
            if(cache[v][cnt] != -1) return cache[v][cnt];
            int coin = coins[v], temp = cnt;
            while (coin > 0 && temp > 0) {
                coin /= 2; temp--;
            }
            long long sum1 = 0, sum2 = 0;
            for(int w : graph[v]) {
                if(w == f) continue;
                sum1 += dfs(w, v, cnt);
                sum2 += dfs(w, v, cnt + 1);
            }
            cache[v][cnt] = max(coin - k + sum1, coin / 2 + sum2);
            return cache[v][cnt];
        };
        return dfs(0, -1, 0);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}