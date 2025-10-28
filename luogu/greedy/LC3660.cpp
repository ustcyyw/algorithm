/**
 * @Time : 2025/10/27-10:49
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3660 2187 贪心 图论
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> ans;
    vector<vector<int>> graph;
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        graph.assign(n, {}), ans.assign(n, -1);
        map<int, vector<int>> mp;
        for(int i = 0, idx = 0; i < n; i++) {
            if(nums[i] > nums[idx]) idx = i;
            graph[i].push_back(idx);
            mp[nums[i]].push_back(i);
        }
        int idx = -1;
        for(auto & it : mp) {
            int temp = -1;
            for(int i : it.second) {
                temp = max(temp, i);
                if(idx != -1 && idx > i) graph[i].push_back(idx);
            }
            idx = max(idx, temp);
        }
        for(int i = 0; i < n; i++) {
            if(ans[i] == -1)
                dfs(nums, i);
        }
        return ans;
    }

    int dfs(vector<int>& nums, int v) {
        if(ans[v] != -1) return ans[v];
        ans[v] = nums[v];
        for(int w : graph[v]) {
            ans[v] = max(ans[v], dfs(nums, w));
        }
        return ans[v];
    }
};