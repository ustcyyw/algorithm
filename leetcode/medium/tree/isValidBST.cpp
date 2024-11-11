/**
 * @Time : 2022/5/30-5:24 PM
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
 * 执行用时：12 ms, 在所有 C++ 提交中击败了53.48%的用户
 * 内存消耗：25.6 MB, 在所有 C++ 提交中击败了5.13%的用户
 *
 * 面试题 04.05. 合法二叉搜索树
 */
class Solution {
public:
    bool valid = true;
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) return true;
        traversal(root);
        return valid;
    }

    vector<int> traversal(TreeNode* root){
        if(!valid) return {};
        int curMin = root->val, curMax = curMin;
        if(root->left != nullptr){
            vector<int> left = traversal(root->left);
            if(left[1] >= root->val)
                valid = false;
            curMin = left[0];
        }
        if(valid && root->right != nullptr){
            vector<int> right = traversal(root->right);
            if(right[0] <= root->val)
                valid = false;
            curMax = right[1];
        }
        if(!valid) return {};
        return {curMin, curMax};
    }
};

int main(){

}
