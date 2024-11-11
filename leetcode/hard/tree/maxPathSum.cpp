/**
 * @Time : 2022/7/7-7:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给定一个二叉树的根节点 root ，返回其 最大路径和，即所有路径上节点值之和的最大值。

 

示例 1：



输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
示例 2：



输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
 

提示：

树中节点数目范围是 [1, 3 * 104]
-1000 <= Node.val <= 1000
 

注意：本题与主站 124 题相同： https://algorithm-cn.com/problems/binary-tree-maximum-path-sum/



来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/jC7MId
 */
class Solution {
public:
    /**
     * 执行用时：16 ms, 在所有 C++ 提交中击败了94.30%的用户
     * 内存消耗：26.9 MB, 在所有 C++ 提交中击败了53.07%的用户
     */
    int res = -100000000;
    int maxPathSum(TreeNode* root) {
        singleMax(root);
        return res;
    }
    // 返回单侧路径最大值
    int singleMax(TreeNode* root){
        if(root == nullptr) return 0;
        int val = root->val, left = singleMax(root->left), right = singleMax(root->right);
        // 可能左右两边的单侧路径都是负贡献,那直接舍弃那一侧
        left = left < 0 ? 0 : left, right = right < 0 ? 0 : right;
        res = max(max(right, left) + val, max(left + right + val, res));
        return max(right, left) + val;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}