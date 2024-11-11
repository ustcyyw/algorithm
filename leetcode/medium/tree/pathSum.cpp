/**
 * @Time : 2022/5/31-9:34 PM
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
     * 执行用时：12 ms, 在所有 C++ 提交中击败了62.97%的用户
     * 内存消耗：19.3 MB, 在所有 C++ 提交中击败了25.07%的用户
     *
     * 回溯+前缀和
     */
    int res = 0;
    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> map;
        map[0] = 1;
        traversal(root, 0, sum, map);
        return res;
    }

    void traversal(TreeNode* root, int sum, int target, unordered_map<int, int>& map){
        if(root == nullptr) return;
        int curSum = sum + root->val, key = curSum - target;
        if(map.find(key) != map.end()) res += map[key];
        map[curSum] = map.find(key) != map.end() ? map[curSum] + 1 : 1;
        traversal(root->left, curSum, target, map);
        traversal(root->right, curSum, target, map);
        map[curSum]--;
    }
};

int main(){

}