/**
 * @Time : 2022/8/2-12:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一棵 树（即一个连通、无向、无环图），根节点是节点 0 ，这棵树由编号从 0 到 n - 1 的 n 个节点组成。用下标从 0 开始、长度为 n 的数组 parent 来表示这棵树，其中 parent[i] 是节点 i 的父节点，由于节点 0 是根节点，所以 parent[0] == -1 。

另给你一个字符串 s ，长度也是 n ，其中 s[i] 表示分配给节点 i 的字符。

请你找出路径上任意一对相邻节点都没有分配到相同字符的 最长路径 ，并返回该路径的长度。

 

示例 1：



输入：parent = [-1,0,0,1,1,2], s = "abacbe"
输出：3
解释：任意一对相邻节点字符都不同的最长路径是：0 -> 1 -> 3 。该路径的长度是 3 ，所以返回 3 。
可以证明不存在满足上述条件且比 3 更长的路径。
示例 2：



输入：parent = [-1,0,0,0], s = "aabc"
输出：3
解释：任意一对相邻节点字符都不同的最长路径是：2 -> 0 -> 3 。该路径的长度为 3 ，所以返回 3 。
 

提示：

n == parent.length == s.length
1 <= n <= 105
对所有 i >= 1 ，0 <= parent[i] <= n - 1 均成立
parent[0] == -1
parent 表示一棵有效的树
s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/longest-path-with-different-adjacent-characters
 */
class Solution {
public:
    /**
     * 执行用时：308 ms, 在所有 C++ 提交中击败了70.39%的用户
     * 内存消耗：173.5 MB, 在所有 C++ 提交中击败了74.02%的用户
     */
    int res = 1;
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> graph = vector(n, vector(0, 0));
        for(int i = 1; i < n; i++){
            int p = parent[i];
            graph[p].push_back(i);
        }
        dfs(graph, s, 0);
        return res;
    }

    int dfs(vector<vector<int>>& graph, string& s, int v){
        if(graph[v].size() == 0) return 1;
        int len1 = -1, len2 = -1;
        for(int w : graph[v]){
            int temp = dfs(graph, s, w);
            if(s[v] != s[w]) {
                if(temp >= len1){
                    len2 = len1;
                    len1 = temp;
                } else if(temp > len2)
                    len2 = temp;
            }
        }
        if(len1 != -1) {
            if(len2 != -1) res = max(res, len1 + len2 + 1);
            else res = max(res, len1 + 1);
        }
        return len1 == -1 ? 1 : len1 + 1;
    }
};

int main(){
    Solution s;
    vector<int> arr = {-1,0,1};
    s.longestPath(arr, "aab");
    cout << 0 << endl;
}