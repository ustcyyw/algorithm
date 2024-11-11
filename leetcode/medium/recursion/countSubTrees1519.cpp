/**
 * @Time : 2023/4/13-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> graph(n);
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        vector<int> res(n, 0);
        dfs(res, graph, labels, 0, -1);
        return res;
    }

    vector<int> dfs(vector<int>& res, vector<vector<int>>& graph, string& labels, int v, int father){
        vector<int> ans(26, 0);
        ans[labels[v] - 'a'] = 1;
        for(int w : graph[v]){
            if(w == father) continue;
            vector<int> temp = dfs(res, graph, labels, w, v);
            for(int i = 0; i < 26; i++)
                ans[i] += temp[i];
        }
        res[v] = ans[labels[v] - 'a'];
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}