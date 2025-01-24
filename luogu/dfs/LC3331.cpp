/**
 * @Time : 2025/1/23-9:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3331 深度优先搜索 在递归中用栈的思路类似于LC3425
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    string s;
    vector<int> parent;
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        this->n = parent.size(), this->parent = parent, this->s = s;
        vector<vector<int>> g1 = build();
        vector<stack<int>> st(26);
        dfs1(g1, st, 0, -1);
        vector<vector<int>> g2 = build();
        vector<int> count(n, 0);
        dfs2(g2, count, 0, -1);
        return count;
    }

    void dfs1(vector<vector<int>>& graph, vector<stack<int>>& st, int v, int f) {
        int idx = s[v] - 'a';
        if(!st[idx].empty()) parent[v] = st[idx].top();
        st[idx].push(v);
        for(int w : graph[v]) {
            if(w == f) continue;
            dfs1(graph, st, w, v);
        }
        st[idx].pop();
    }

    void dfs2(vector<vector<int>>& graph, vector<int>& count, int v, int f) {
        count[v] = 1;
        for(int w : graph[v]) {
            if(w == f) continue;
            dfs2(graph, count, w, v);
            count[v] += count[w];
        }
    }

    vector<vector<int>> build() {
        vector<vector<int>> graph(n);
        for(int i = 1; i < n; i++)
            graph[parent[i]].push_back(i);
        return graph;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}