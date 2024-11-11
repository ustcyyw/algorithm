/**
 * @Time : 2023/3/29-10:33 PM
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
    map<int, vector<int>> map;
    unordered_map<int, int> layer; // val -> layer的映射
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs(root, 0, 0);
        vector<vector<int>> res;
        for(auto& pair : map){
            vector<int>& arr = pair.second;
            sort(arr.begin(), arr.end(), [&](int& a, int& b) -> bool {
                return layer[a] == layer[b] ? a < b : layer[a] < layer[b];
            });
            res.push_back(arr);
        }
        return res;
    }

    void dfs(TreeNode* node, int x, int y){
        if(node == nullptr) return;
        layer[node->val] = y;
        if(!map.count(x)) map[x] = {};
        map[x].push_back(node->val);
        dfs(node->left, x - 1, y + 1);
        dfs(node->right, x + 1, y + 1);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}