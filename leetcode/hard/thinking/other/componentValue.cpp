/**
 * @Time : 2022/10/16-1:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 有一棵 n 个节点的无向树，节点编号为 0 到 n - 1 。

给你一个长度为 n 下标从 0 开始的整数数组 nums ，其中 nums[i] 表示第 i 个节点的值。同时给你一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 与 bi 之间有一条边。

你可以 删除 一些边，将这棵树分成几个连通块。一个连通块的 价值 定义为这个连通块中 所有 节点 i 对应的 nums[i] 之和。

你需要删除一些边，删除后得到的各个连通块的价值都相等。请返回你可以删除的边数 最多 为多少。

 

示例 1：



输入：nums = [6,2,2,2,6], edges = [[0,1],[1,2],[1,3],[3,4]]
输出：2
解释：上图展示了我们可以删除边 [0,1] 和 [3,4] 。得到的连通块为 [0] ，[1,2,3] 和 [4] 。每个连通块的价值都为 6 。可以证明没有别的更好的删除方案存在了，所以答案为 2 。
示例 2：

输入：nums = [2], edges = []
输出：0
解释：没有任何边可以删除。
 

提示：

1 <= n <= 2 * 104
nums.length == n
1 <= nums[i] <= 50
edges.length == n - 1
edges[i].length == 2
0 <= edges[i][0], edges[i][1] <= n - 1
edges 表示一棵合法的树。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/create-components-with-same-value
 */
class Solution {
public:
    /**
     * 注意题目给出的是一颗树
     *
     * 连通块的个数为n，那么要删除的边数就是n-1
     * 设整棵数的和为total
     * 如果total % n = 0，可能可以将树分为n块并且每一块的值为 total / n
     * 需要判断是否可以将树分为n个值为target = total / n的子树
     *
     * 枚举连通块的个数
     *
     * dfs(int v, int target):返回一颗以v为根的树的价值：
     * 如果该树的价值为target，那么返回0表示它自己要成为一个连通块的起点，其父节点和它断开链接
     * 如果该树的价值小于target，还不够成为一个块，要与其父节点连在一起再查看
     * 如果该树的价值大于target，这个块超过了，就导致整个树无法划分成n个值为target的子树，直接返回-1
     *
     * 最后这种情况的出现，是因为v的子树本身不够target，要和v连在一起，可能有一个或多个子树连在v上，就超过了target。
     * 不让他们连，就会子树的值不足target，也是不满足题意。
     * 因此返回-1
     */
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> graph(n, vector(0, 0));
        for(auto & edge : edges){
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        int total = accumulate(nums.begin(), nums.end(), 0);
        for(int i = n; i > 1; i--){
            if(total % i != 0) continue;
            if(dfs(graph, nums, 0, -1, total / i) != -1) return i - 1;
        }
        return 0;
    }

    int dfs(vector<vector<int>>& graph, vector<int>& nums, int v, int father, int target){
        int val = nums[v];
        for(int w : graph[v]){
            if(w == father) continue; // father用于保证递归的顺序，确定子树和父结点
            int t = dfs(graph, nums, w, v, target);
            if(t == -1 || val + t > target) return -1; // 有一个子树无法完成划分，就直接返回-1
            val += t;
        }
        if(val == target) return 0;
        return val > target ? -1 : val;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}