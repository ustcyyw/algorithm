/**
 * @Time : 2023/4/16-5:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 现有一棵无向、无根的树，树中有 n 个节点，按从 0 到 n - 1 编号。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间存在一条边。

每个节点都关联一个价格。给你一个整数数组 price ，其中 price[i] 是第 i 个节点的价格。

给定路径的 价格总和 是该路径上所有节点的价格之和。

另给你一个二维整数数组 trips ，其中 trips[i] = [starti, endi] 表示您从节点 starti 开始第 i 次旅行，并通过任何你喜欢的路径前往节点 endi 。

在执行第一次旅行之前，你可以选择一些 非相邻节点 并将价格减半。

返回执行所有旅行的最小价格总和。

 

示例 1：


输入：n = 4, edges = [[0,1],[1,2],[1,3]], price = [2,2,10,6], trips = [[0,3],[2,1],[2,3]]
输出：23
解释：
上图表示将节点 2 视为根之后的树结构。第一个图表示初始树，第二个图表示选择节点 0 、2 和 3 并使其价格减半后的树。
第 1 次旅行，选择路径 [0,1,3] 。路径的价格总和为 1 + 2 + 3 = 6 。
第 2 次旅行，选择路径 [2,1] 。路径的价格总和为 2 + 5 = 7 。
第 3 次旅行，选择路径 [2,1,3] 。路径的价格总和为 5 + 2 + 3 = 10 。
所有旅行的价格总和为 6 + 7 + 10 = 23 。可以证明，23 是可以实现的最小答案。
示例 2：


输入：n = 2, edges = [[0,1]], price = [2,2], trips = [[0,0]]
输出：1
解释：
上图表示将节点 0 视为根之后的树结构。第一个图表示初始树，第二个图表示选择节点 0 并使其价格减半后的树。
第 1 次旅行，选择路径 [0] 。路径的价格总和为 1 。
所有旅行的价格总和为 1 。可以证明，1 是可以实现的最小答案。
 

提示：

1 <= n <= 50
edges.length == n - 1
0 <= ai, bi <= n - 1
edges 表示一棵有效的树
price.length == n
price[i] 是一个偶数
1 <= price[i] <= 1000
1 <= trips.length <= 100
0 <= starti, endi <= n - 1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimize-the-total-price-of-the-trips
 */
class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<vector<int>>graph(n);
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        // 标记每个点被访问多少次
        vector<int> cnt(n, 0);
        function<bool(int, int, int)> dfs = [&](int v, int target, int father) -> bool{
            if(v == target) return true;
            for(int w : graph[v]){
                if(w == father) continue;
                if(dfs(w, target, v)) {
                    cnt[v]++;
                    return true;
                }
            }
            return false;
        };
        for(auto& trip : trips){
            cnt[trip[1]]++;
            dfs(trip[0], trip[1], -1);
        }
        // 树形dp 类似于打家劫舍
        vector<vector<int>> f;
        function<void(int,int)> minCost = [&](int v, int father) -> void {
            f[0][v] = price[v] * cnt[v], f[1][v] = f[0][v] / 2;
            for(int w : graph[v]){
                if(w == father) continue;
                minCost(w, v);
                f[1][v] += f[0][w]; // 当前点要半价，子结点只能不半价
                f[0][v] += min(f[0][w], f[1][w]); // 当前全价，子结点可半价，可全价
            }
        };
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            f.assign(2, vector<int>(n, INT_MAX));
            minCost(i, -1);
            res = min(res, min(f[1][i], f[0][i]));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}