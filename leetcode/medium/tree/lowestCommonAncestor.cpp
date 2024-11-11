/**
 * @Time : 2022/5/31-10:57 AM
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
    TreeNode* res;
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        traversal(root, p, q);
        return res;
    }

    bool traversal(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root == nullptr) return false;
        bool left = traversal(root->left, p, q), right = traversal(root->right, p, q);
        if(root->val == p->val || root->val == q->val){
            if(left || right) res = root;
            return true;
        }
        if(left && right) res = root;
        if(left || right) return true;
        return false;
    }
};

int main(){

}