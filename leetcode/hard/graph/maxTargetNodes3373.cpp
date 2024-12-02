/**
 * @Time : 2024/12/2-9:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3373 图论 二分图
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 容易想到要递归计算某一个结点离它的距离为偶数/奇数的结点数目
     * 先假设根是0，并且结点v和w到0的距离分别是2i、2j两个偶数
     * 1. v和w的lca就是0，那么dis(v,w) = 2(i + j)是偶数
     * 2. v和w的lca不是0，记为t。如果dis(t,0)是奇数 那么dis(v,t)和dis(w,t)也是奇数
     *    dis(v,w)是两个奇数之和 是偶数；如果dis(t,0)是偶数，同理
     * 因此与根结点距离为偶数的所有结点 相互之间的距离也都是偶数
     * 与根结点距离为奇数的结点也同理，他们相互之间的距离是偶数。
     * 也就是按与0的距离分成的两个集合，集合内的所有结点互为目标结点
     *
     * 然后考虑连tree2 对于tree1中的任意结点i
     * 如果将i与tree2根结点root2链接，tree2中任意结点j，dis(i,j) = dis(i,root) + dis(root,j)
     * 因为到root2距离为奇数的所有点就会成为i的目标结点
     * 如果用i的相邻结点与root2链接，到root2距离为偶数的所有点就会成为i的目标结点
     * 所以i可以选择将root2两个集合中大的那个变为自己的目标结点
     * 因为已经说明了结点集合中结点等价 i连接root2和连接tree2中任何一个结点都没本质区别
     */
    int one1[N], two1[N], one2[N], two2[N], depth1[N], depth2[N];
    vector<vector<int>> build(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for(auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        return graph;
    }

    void dfs1(vector<vector<int>>& graph, int v, int f, int* one, int* two, int* depth) {
        depth[v] = f == -1 ? 0 : depth[f] + 1;
        two[v] = 1, one[v] = 0;
        for(int w : graph[v]) {
            if(w == f) continue;
            dfs1(graph, w, v, one, two, depth);
            one[v] += two[w], two[v] += one[w];
        }
    }

    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1, m = edges2.size() + 1;
        vector<vector<int>> g1 = build(n, edges1), g2 = build(m, edges2);
        dfs1(g1, 0, -1, one1, two1, depth1);
        dfs1(g2, 0, -1, one2, two2, depth2);
        vector<int> ans(n, 0);
        for(int i = 0, val = max(one2[0], two2[0]); i < n; i++)
            ans[i] = (depth1[i] % 2 == 0 ? two1[0] : one1[0]) + val;
        return ans;
    }
};