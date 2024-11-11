/**
 * @Time : 2022/12/18-1:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个有 n 个节点的 无向 图，节点编号为 1 到 n 。再给你整数 n 和一个二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 和 bi 之间有一条边。图不一定连通。

你可以给图中添加 至多 两条额外的边（也可以一条边都不添加），使得图中没有重边也没有自环。

如果添加额外的边后，可以使得图中所有点的度数都是偶数，返回 true ，否则返回 false 。

点的度数是连接一个点的边的数目。

 

示例 1：



输入：n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
输出：true
解释：上图展示了添加一条边的合法方案。
最终图中每个节点都连接偶数条边。
示例 2：



输入：n = 4, edges = [[1,2],[3,4]]
输出：true
解释：上图展示了添加两条边的合法方案。
示例 3：



输入：n = 4, edges = [[1,2],[1,3],[1,4]]
输出：false
解释：无法添加至多 2 条边得到一个符合要求的图。
 

提示：

3 <= n <= 105
2 <= edges.length <= 105
edges[i].length == 2
1 <= ai, bi <= n
ai != bi
图中不会有重边

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/add-edges-to-make-degrees-of-all-nodes-even
 */
class Solution {
public:
    vector<unordered_set<int>> graph;
    bool isPossible(int n, vector<vector<int>>& edges) {
        graph.assign(n + 1, {});
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].insert(w); graph[w].insert(v);
        }
        vector<int> nodes; // 度数为奇数的结点
        for(int i = 1; i <= n; i++){
            if(graph[i].size() % 2 == 1) nodes.push_back(i);
            if(nodes.size() > 4) return false; // 一条边最多能消除2个奇数度数的结点，如果有多于四个奇数结点，肯定不行
        }
        if(nodes.empty()) return true;
        // 新增一条边 连接两个奇数结点，消除2个奇数结点；连接一个奇数结点和一个偶数结点，奇数结点数量保持不变。
        // 也就是说 只有偶数个奇数结点才能被消除
        if(nodes.size() % 2 == 1) return false;
        if(nodes.size() == 2) return check(nodes[0], nodes[1]) != -1;
        return check(nodes[0], nodes[1], nodes[2], nodes[3])
        || check(nodes[0], nodes[2], nodes[1], nodes[3])
        || check(nodes[0], nodes[3], nodes[1], nodes[2]);
    }

    // 两个奇数度数的结点， 要进行消除
    // 1. 他们两个之间不存在边 将他们两个连起来
    // 2. 找一个中介结点，这个中介与他们两个都不存边。他们两分别与中介连接 添加2条边
    int check(int v, int w){
        if(!graph[v].count(w)) return 1;
        for(int k = 1; k < graph.size(); k++){
            if(k == v || k == w) continue;
            if(!graph[k].count(v) && !graph[k].count(w)) return 2;
        }
        return -1;
    }

    bool check(int a, int b, int c, int d){
        return !graph[a].count(b) && graph[c].count(d);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}