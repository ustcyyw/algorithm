/**
 * @Time : 2022/7/25-7:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 有向图 ，它含有 n 个节点和 m 条边。节点编号从 0 到 n - 1 。

给你一个字符串 colors ，其中 colors[i] 是小写英文字母，表示图中第 i 个节点的 颜色 （下标从 0 开始）。同时给你一个二维数组 edges ，其中 edges[j] = [aj, bj] 表示从节点 aj 到节点 bj 有一条 有向边 。

图中一条有效 路径 是一个点序列 x1 -> x2 -> x3 -> ... -> xk ，对于所有 1 <= i < k ，从 xi 到 xi+1 在图中有一条有向边。路径的 颜色值 是路径中 出现次数最多 颜色的节点数目。

请你返回给定图中有效路径里面的 最大颜色值 。如果图中含有环，请返回 -1 。

 

示例 1：



输入：colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
输出：3
解释：路径 0 -> 2 -> 3 -> 4 含有 3 个颜色为 "a" 的节点（上图中的红色节点）。
示例 2：



输入：colors = "a", edges = [[0,0]]
输出：-1
解释：从 0 到 0 有一个环。
 

提示：

n == colors.length
m == edges.length
1 <= n <= 105
0 <= m <= 105
colors 只含有小写英文字母。
0 <= aj, bj < n


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/largest-color-value-in-a-directed-graph
 */
class Solution {
public:
    int n;
    bool hasCycle = false;
    vector<vector<int>> cache; // cache[i][j] 以i为起点的路径上，字母j的最大出现次数
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        n = colors.size();
        cache.assign(n, {});
        vector<vector<int>> graph = vector(n, vector(0, 0));
        vector<int> degree = vector(n, 0); // 统计入度
        for(vector<int>& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w);
            degree[w]++;
        }
        int countZero = 0;;
        for(int i = 0; i < n; i++)
            if(degree[i] == 0) countZero++;
        if(countZero == 0) return -1; // 没有入度为0的点，一定是有环
        vector<bool> onStack = vector(n, false);
        int res = -1;
        for(int v = 0; v < n; v++){ // 理论上最大值是以入度为0的点为起点的，但是还要判断环是否存在，因此要遍历每一个点
            if(cache[v].size() != 0) continue; // 说明是已经访问过的点
            vector<int> info = dfs(graph, onStack, colors, v);
            if(hasCycle) return -1;
            if(degree[v] == 0)
                res = max(res, getMax(info));
        }
        return res;
    }

    vector<int> dfs(vector<vector<int>>& graph, vector<bool>& onStack, string& colors, int v){
        if(hasCycle) return {};
        if(cache[v].size() != 0) return cache[v];
        onStack[v] = true;
        vector<int> info = vector(26, 0);
        for(int w : graph[v]){
            if(onStack[w]) {
                hasCycle = true;
                break;
            }
            vector<int> cur = dfs(graph, onStack, colors, w);
            for(int i = 0; i < 26; i++)
                info[i] = max(info[i], cur[i]);
        }
        info[colors[v] - 'a']++;
        onStack[v] = false;
        cache[v] = info;
        return info;
    }

    int getMax(vector<int>& arr){
        int res = 0;
        for(int& num : arr)
            res = max(res, num);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}