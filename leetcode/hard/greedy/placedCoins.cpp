/**
 * @Time : 2023/12/24-12:23 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛120 t4
 */

/*
 * 三个数的最大乘积 要么是三个最大的数乘出来的 要么是最小的两个数（都为负的情况）乘最大的数
 * 所以只要保留最大的3个数和最小的2个数即可
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        vector<int> size(n, 0);
        vector<vector<int>> graph(n);
        vector<ll> ans(n, 0);
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        function<vector<vector<ll>>(int, int)> dfs = [&](int v, int f) -> vector<vector<ll>> {
            vector<ll> arr1, arr2;
            arr1.push_back(cost[v]), arr2.push_back(cost[v]);
            for(int w : graph[v]) {
                if(w == f) continue;
                vector<vector<ll>> temp = dfs(w, v);
                size[v] += size[w];
                for(long long& num : temp[0])
                    arr1.push_back(num);
                for(long long& num : temp[1])
                    arr2.push_back(num);
            }
            if(++size[v] < 3) {
                ans[v] = 1;
                return {arr1, arr2};
            }
            sort(arr1.begin(), arr1.end()), sort(arr2.begin(), arr2.end());
            int n1 = arr1.size();
            long long a1 = arr1[n1 - 1], b1 = arr1[n1 - 2], c1 = arr1[n1 - 3];
            long long a2 = arr2[0], b2 = arr2[1];
            ans[v] = max({0ll, a1 * b1 * c1, a2 * b2 * a1});
            return {{a1, b1, c1}, {a2, b2}};
        };
        dfs(0, -1);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}