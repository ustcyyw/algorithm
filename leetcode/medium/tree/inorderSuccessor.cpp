/**
 * @Time : 2022/5/31-9:52 AM
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

class Solution {
public:
    /**
     * 如果当前结点就是p，那么应该找到p右子树的最小值
     * 如果当前结点比p小，说明答案在当前结点的右子树
     * 如果当前结点比p大，答案可能是当前结点（其左子树中最大的结点就是p时），
     *     也可能要去左子树中找答案（对应着左子树中p不是最大值）
     *
     * 执行用时：24 ms, 在所有 C++ 提交中击败了88.94%的用户
     * 内存消耗：22.3 MB, 在所有 C++ 提交中击败了51.58%的用户
     */
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(root == nullptr) return nullptr;
        if(root->val == p->val)
            return root->right == nullptr ? nullptr : minNode(root->right);
        else if(root->val < p->val)
            return inorderSuccessor(root->right, p);
        else {
            TreeNode* temp = inorderSuccessor(root->left, p);
            return temp == nullptr ? root : temp;
        }
    }

    TreeNode* minNode(TreeNode* root){
        if(root->left == nullptr) return root;
        return minNode(root->left);
    }
};

int main(){

}