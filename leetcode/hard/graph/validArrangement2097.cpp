/**
 * @Time : 2022/8/27-6:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的二维整数数组 pairs ，其中 pairs[i] = [starti, endi] 。如果 pairs 的一个重新排列，满足对每一个下标 i （ 1 <= i < pairs.length ）都有 endi-1 == starti ，那么我们就认为这个重新排列是 pairs 的一个 合法重新排列 。

请你返回 任意一个 pairs 的合法重新排列。

注意：数据保证至少存在一个 pairs 的合法重新排列。

 

示例 1：

输入：pairs = [[5,1],[4,5],[11,9],[9,4]]
输出：[[11,9],[9,4],[4,5],[5,1]]
解释：
输出的是一个合法重新排列，因为每一个 endi-1 都等于 starti 。
end0 = 9 == 9 = start1
end1 = 4 == 4 = start2
end2 = 5 == 5 = start3
示例 2：

输入：pairs = [[1,3],[3,2],[2,1]]
输出：[[1,3],[3,2],[2,1]]
解释：
输出的是一个合法重新排列，因为每一个 endi-1 都等于 starti 。
end0 = 3 == 3 = start1
end1 = 2 == 2 = start2
重新排列后的数组 [[2,1],[1,3],[3,2]] 和 [[3,2],[2,1],[1,3]] 都是合法的。
示例 3：

输入：pairs = [[1,2],[1,3],[2,1]]
输出：[[1,2],[2,1],[1,3]]
解释：
输出的是一个合法重新排列，因为每一个 endi-1 都等于 starti 。
end0 = 2 == 2 = start1
end1 = 1 == 1 = start2
 

提示：

1 <= pairs.length <= 105
pairs[i].length == 2
0 <= starti, endi <= 109
starti != endi
pairs 中不存在一模一样的数对。
至少 存在 一个合法的 pairs 重新排列。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/valid-arrangement-of-pairs
 */
class Solution {
public:
    /**
     * 本题但模型 与332 一样，都是欧拉通路（回路）相关的
     * ac 但耗时1100ms 太慢
     */
//    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
//        // 建图，并且计算出度与入度的差
//        unordered_map<int, int> degree_diff; // 结点的 出度 - 入度
//        unordered_map<int, queue<int>> graph;
//        for(auto& pair : pairs){
//            int v = pair[0], w = pair[1];
//            if(!graph.count(v)) graph[v] = {};
//            graph[v].push(w);
//            degree_diff[v]++, degree_diff[w]--;
//        }
//        // 找起点欧拉路径的起点，如果所有点的出度=入度，说明是欧拉回路，从任意一点开始都可以
//        int start = -1, temp = -1;
//        for(auto& p : degree_diff){
//            temp = p.first;
//            if(p.second == 1) {
//                start = p.first;
//                break;
//            }
//        }
//        if(start == -1) start = temp;
//        // dfs 找到欧拉路径
//        vector<int> nodes; //存放结点的逆后续
//        dfs(graph, nodes, start);
//        vector<vector<int>> res;
//        for(int i = nodes.size() - 1; i > 0; i--)
//            res.push_back({nodes[i], nodes[i - 1]});
//        return res;
//    }
//
//    void dfs(unordered_map<int, queue<int>>& graph, vector<int>& nodes, int v){
//        while(graph.count(v) && !graph[v].empty()){
//            int w = graph[v].front();
//            graph[v].pop();
//            dfs(graph, nodes, w);
//        }
//        nodes.push_back(v);
//    }

    /**
    * 学习别人的写法
     * 执行用时：856 ms, 在所有 C++ 提交中击败了56.00%的用户
     * 内存消耗：268.5 MB, 在所有 C++ 提交中击败了82.67%的用户
    */
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        // 建图，并且计算出度与入度的差
        unordered_map<int, int> degree_diff; // 结点的 出度 - 入度
        unordered_map<int, vector<int>> graph;
        for(auto& pair : pairs){
            int v = pair[0], w = pair[1];
            graph[v].push_back(w);
            degree_diff[v]++, degree_diff[w]--;
        }
        // 找起点欧拉路径的起点，如果所有点的出度=入度，说明是欧拉回路，从任意一点开始都可以
        int start = -1;
        for(auto& p : degree_diff){
            if(p.second == 1) {
                start = p.first;
                break;
            }
        }
        if(start == -1) start = degree_diff.begin()->first;
        // dfs 找到欧拉路径
        vector<vector<int>> res;
        dfs(graph, res, start);
        reverse(res.begin(), res.end());
        return res;
    }

    void dfs(unordered_map<int, vector<int>>& graph, vector<vector<int>>& res, int v){
        while(graph.count(v) && !graph[v].empty()){
            int w = graph[v].back();
            graph[v].pop_back();
            dfs(graph, res, w);
            res.push_back({v, w}); // 存放边的做法与存放结点的做法 有区别，但都是逆后序
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}