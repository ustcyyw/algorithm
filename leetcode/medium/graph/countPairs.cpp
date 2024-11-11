/**
 * @Time : 2022/6/28-11:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给你一个整数 n ，表示一张 无向图 中有 n 个节点，编号为 0 到 n - 1 。同时给你一个二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 和 bi 之间有一条 无向 边。

请你返回 无法互相到达 的不同 点对数目 。

 

示例 1：



输入：n = 3, edges = [[0,1],[0,2],[1,2]]
输出：0
解释：所有点都能互相到达，意味着没有点对无法互相到达，所以我们返回 0 。
示例 2：



输入：n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
输出：14
解释：总共有 14 个点对互相无法到达：
[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]]
所以我们返回 14 。
 

提示：

1 <= n <= 105
0 <= edges.length <= 2 * 105
edges[i].length == 2
0 <= ai, bi < n
ai != bi
不会有重复边。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph
 */
class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph = build(n, edges);
        vector<bool> marked = vector(n, false);
        long long res = 0;
        for(int i = 0; i < n; i++){
            if(marked[i]) continue;
            long count = (long)dfs(graph, marked, i);
            res += (n - count) * count;
        }
        return res / 2;
    }

    int dfs(vector<vector<int>>& graph, vector<bool>& marked, int v){
        marked[v] = true;
        int count = 1;
        for(int w : graph[v]){
            if(!marked[w]) count += dfs(graph, marked, w);
        }
        return count;
    }

    vector<vector<int>> build(int n, vector<vector<int>>& edges){
        vector<vector<int>> graph = vector(n, vector(0, 0));
        for(vector<int>& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        return graph;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}