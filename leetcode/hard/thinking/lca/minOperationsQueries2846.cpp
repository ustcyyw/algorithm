/**
 * @Time : 2023/9/4-9:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
vector<int> depth;
vector<vector<int>> cnt, f;
vector<vector<vector<int>>> graph;

class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries) {
        depth = vector(n, 0), cnt = vector(n, vector(27, 0)), f = vector(n, vector(32, 0));
        graph.assign(n, {});
        for (vector<int> &edge: edges) {
            int v = edge[0], w = edge[1], weight = edge[2];
            graph[v].push_back({v, w, weight}), graph[w].push_back({w, v, weight});
        }
        dfs(0, -1, -1);
        vector<int> ans;
        for(auto& q : queries) {
            int v = q[0], w = q[1], father = lca(v, w), t = 0;
            for(int i = 1; i <= 26; i++)
                t = max(t, cnt[v][i] + cnt[w][i] - 2 * cnt[father][i]);
            ans.push_back(depth[v] + depth[w] - 2 * depth[father] - t);
        }
        return ans;
    }

    void dfs(int v, int father, int weight) {
        depth[v] = father == -1 ? 0 : depth[father] + 1; // 更新到达结点w的路径的长度
        if (father != -1) { // 更新到达结点w的路径的权重统计情况
            for (int i = 1; i <= 26; i++)
                cnt[v][i] = cnt[father][i];
            cnt[v][weight]++;
        }
        f[v][0] = father;
        for (int j = 1; j < 31 && f[v][j - 1] != -1; j++)
            f[v][j] = f[f[v][j - 1]][j - 1];
        for (auto &edge: graph[v]) {
            if (edge[1] == father) continue;
            dfs(edge[1], v, edge[2]);
        }
    }

    int getKthAncestor(int node, int k) {
        if (depth[node] < k) return -1;
        for (int i = 0; i < 31; i++) {
            if (((1 << i) & k) > 0)
                node = f[node][i];
        }
        return node;
    }

    int lca(int x, int y) {
        if (depth[x] > depth[y]) swap(x, y); // 确保y比x深度更深
        y = getKthAncestor(y, depth[y] - depth[x]); // 保证x和y同一深度
        if (x == y) return y;
        // 找到第一个不是它们祖先的两个点。
        for (int j = 30; j >= 0 && y != x; --j) {
            if (f[x][j] != f[y][j])
                x = f[x][j], y = f[y][j];
        }
        return f[x][0];
    }
};