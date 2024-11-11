/**
 * @Time : 2022/4/26-11:16 AM
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> vals1, vals2;
        leafVals(root1, vals1), leafVals(root2, vals2);
        if(vals1.size() != vals2.size()) return false;
        for(int i = 0; i < vals1.size(); i++)
            if(vals1[i] != vals2[i]) return false;
        return true;
    }

    void leafVals(TreeNode* root, vector<int>& vals){
        if(root->left == nullptr && root->right == nullptr){
            vals.push_back(root->val);
            return;
        }
        if(root->left != nullptr) leafVals(root->left, vals);
        if(root->right != nullptr) leafVals(root->right, vals);
    }
};

int main(){

}