/**
 * @Time : 2023/3/2-9:21 PM
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
    const int N = 501;
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if(k == 0) return {target->val};
        vector<vector<int>> graph = vector(N, vector(0, 0));
        dfs(root, graph);
        vector<bool> marked(N, false);
        marked[target->val] = true;
        queue<int> queue;
        queue.push(target->val);
        vector<int> res;
        while (k > 0){
            int sz = queue.size();
            for(int i = 0; i < sz; i++) {
                int v = queue.front();
                queue.pop();
                for(int w : graph[v]){
                    if(marked[w]) continue;
                    marked[w] = true;
                    if(k == 1) res.push_back(w);
                    else queue.push(w);
                }
            }
            k--;
        }
        return res;
    }

    void dfs(TreeNode* x, vector<vector<int>>& graph){
        int v = x->val;
        if(x->left != nullptr){
            graph[v].push_back(x->left->val);
            graph[x->left->val].push_back(v);
            dfs(x->left, graph);
        }
        if(x->right != nullptr){
            graph[v].push_back(x->right->val);
            graph[x->right->val].push_back(v);
            dfs(x->right, graph);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}