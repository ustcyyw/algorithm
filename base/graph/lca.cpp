/**
 * @Time : 2023/11/2-11:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> depth;
    vector<vector<int>> f;
    void LCA(vector<vector<int>>& tree, int s) {
        int n = tree.size();
        depth.assign(n, 0);
        f = vector(n, vector(31, -1)); // 必须初始值为-1
        function<void(int, int)> dfs = [&](int v, int father) {
            if(father != -1) depth[v] = depth[father] + 1;
            f[v][0] = father;
            for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
                f[v][j] = f[f[v][j - 1]][j - 1];
            for(int w : tree[v]) {
                if(w != father)
                    dfs(w, v);
            }
        };
        dfs(s, -1);
    }
    // 找到v的向上数的第k个祖先结点
    int get_ancestor(int v, int k) {
        if(depth[v] < k) return -1;
        for(int j = 0; j < 31; j++) {
            if((1 << j) & k)
                v = f[v][j];
        }
        return v;
    }

    int lca(int x, int y) {
        if(depth[x] > depth[y]) swap(x, y); // 确保y比x深度更深
        y = get_ancestor(y, depth[y] - depth[x]); // 保证x和y同一深度
        if(x == y) return y;
        // 找到第一个不是它们祖先的两个点。
        for(int j = 30; j >= 0 && x != y; j--) {
            if(f[x][j] != f[y][j])
                x = f[x][j], y = f[y][j];
        }
        return f[x][0];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}