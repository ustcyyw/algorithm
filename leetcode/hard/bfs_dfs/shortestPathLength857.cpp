/**
 * @Time : 2023/2/27-8:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 存在一个由 n 个节点组成的无向连通图，图中的节点按从 0 到 n - 1 编号。

给你一个数组 graph 表示这个图。其中，graph[i] 是一个列表，由所有与节点 i 直接相连的节点组成。

返回能够访问所有节点的最短路径的长度。你可以在任一节点开始和停止，也可以多次重访节点，并且可以重用边。

 

示例 1：


输入：graph = [[1,2,3],[0],[0],[0]]
输出：4
解释：一种可能的路径为 [1,0,2,0,3]
示例 2：



输入：graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
输出：4
解释：一种可能的路径为 [0,1,4,2,3]
 

提示：

n == graph.length
1 <= n <= 12
0 <= graph[i].length < n
graph[i] 不包含 i
如果 graph[a] 包含 b ，那么 graph[b] 也包含 a
输入的图总是连通图

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/shortest-path-visiting-all-nodes
 */
class Solution {
public:
    /*
     * 最多有12个结点，容易想到用状态压缩的方式表示结点的访问情况
     * 另外，题目中从哪一个结点开始都可以，从哪一个结点结束都可以
     * 因而对于访问完所有结点的状态，最终访问的是哪一点，也是不同的
     * 本题就需要从两个维度描述：1.访问状态 2.到达某访问状态最后访问的是哪个结点
     *
     * 本题中的图是一个无权图，寻找最短路可以使用bfs
     * 注意：bfs处理的最短路问题，应该理解为到达某个状态的最短距离，状态可以有很多个维度来描述
     * 常见的处理到达某个点的最短距离问题，只是状态仅有一个维度，即点的坐标（或者编号）
     */
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size(), u = (1 << n) - 1, step = 0;
        if(n == 1) return 0;
        unordered_set<int> marked;
        queue<int> queue;
        for(int i = 0; i < n; i++){
            int key = (1 << i) * 100 + i;
            queue.push(key); marked.insert(key);
        }
        while (true){
            step++;
            int sz = queue.size();
            for(int k = 0; k < sz; k++){
                int key = queue.front(), s = key / 100, v = key % 100;
                for(int w : graph[v]){
                    int ns = s | (1 << w), nk = ns * 100 + w;
                    if(ns == u) return step;
                    if(!marked.count(nk)) queue.push(nk), marked.insert(nk);
                }
                queue.pop();
            }
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}