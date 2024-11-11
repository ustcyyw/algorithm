/**
 * @Time : 2022/8/4-4:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 n 个节点的 无向图 ，节点编号为 0 到 n - 1 。

给你一个下标从 0 开始的整数数组 scores ，其中 scores[i] 是第 i 个节点的分数。同时给你一个二维整数数组 edges ，其中 edges[i] = [ai, bi] ，表示节点 ai 和 bi 之间有一条 无向 边。

一个合法的节点序列如果满足以下条件，我们称它是 合法的 ：

序列中每 相邻 节点之间有边相连。
序列中没有节点出现超过一次。
节点序列的分数定义为序列中节点分数之 和 。

请你返回一个长度为 4 的合法节点序列的最大分数。如果不存在这样的序列，请你返回 -1 。

 

示例 1：



输入：scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
输出：24
解释：上图为输入的图，节点序列为 [0,1,2,3] 。
节点序列的分数为 5 + 2 + 9 + 8 = 24 。
观察可知，没有其他节点序列得分和超过 24 。
注意节点序列 [3,1,2,0] 和 [1,0,2,3] 也是合法的，且分数为 24 。
序列 [0,3,2,4] 不是合法的，因为没有边连接节点 0 和 3 。
示例 2：



输入：scores = [9,20,6,4,11,12], edges = [[0,3],[5,3],[2,4],[1,3]]
输出：-1
解释：上图为输入的图。
没有长度为 4 的合法序列，所以我们返回 -1 。
 

提示：

n == scores.length
4 <= n <= 5 * 104
1 <= scores[i] <= 108
0 <= edges.length <= 5 * 104
edges[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
不会有重边。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-score-of-a-node-sequence
 */
class Solution {
public:
    /**
     * 关键：在枚举图的时候，也可以考虑从边的角度去枚举
     * 有4个结点，且结点不能重复的路径，设为 a-x-y-b
     * 在枚举边的时候，可以假定我们枚举的边是中间的 x-y 那么对于这一个边能构成的最大路径
     * 就是在x找一个临接点，且不等于y和b；在y找一个临接点,且不等于x和a
     * 由于x/y的临接点只有两个不能取，所以只要保留某个结点3个最大的临接点，就一定能找到合法的最大临接点
     */
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();
        vector<vector<int>> max_nodes = vector(n, vector(3, -1)); // 存的是分值前三的结点id
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            update_point(scores, max_nodes[v], w, scores[w]);
            update_point(scores, max_nodes[w], v, scores[v]);
        }
        int res = -1;
        for(auto& edge : edges){
            int v = edge[0], w = edge[1];
            vector<int>& v_nodes = max_nodes[v], w_nodes = max_nodes[w];
            for(int i = 0; i < 3 && v_nodes[i] != -1; i++){
                if(v_nodes[i] == w) continue; // v的临接点不能于w相同
                for(int j = 0; j < 3 && w_nodes[j] != -1; j++){
                    if(w_nodes[j] == v || w_nodes[j] == v_nodes[i]) continue; // w的临接点不能于v和选出的a相同
                    res = max(res, scores[v] + scores[w] + scores[v_nodes[i]] + scores[w_nodes[j]]);
                }
            }
        }
        return res;
    }
    // 维护分数前三的结点的id
    void update_point(vector<int>& scores, vector<int>& arr, int id, int point){
        if(arr[0] == -1 || scores[arr[0]] <= point){
            arr[2] = arr[1]; arr[1] = arr[0]; arr[0] = id;
        } else if(arr[1] == -1 || scores[arr[1]] <= point){
            arr[2] = arr[1]; arr[1] = id;
        } else if(arr[2] == -1 || scores[arr[2]] < point)
            arr[2] = id;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}