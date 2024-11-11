/**
 * @Time : 2023/11/3-12:38 AM
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
    vector<int> closestNode(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<vector<int>> tree(n);
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            tree[v].push_back(w), tree[w].push_back(v);
        }
        depth.assign(n, 0);
        f = vector(n, vector(31, 0));
        function<void(int, int)> dfs = [&](int v, int father) -> void {
            if(father != -1) depth[v] = depth[father] + 1;
            f[v][0] = father;
            for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
                f[v][j] = f[f[v][j - 1]][j - 1];
            for(int w : tree[v]) {
                if(w != father)
                    dfs(w, v);
            }
        };
        dfs(0, -1);
        vector<int> res;
        for(auto& q : query) {
            int s = q[0], e = q[1], t = q[2], father = lca(s, e);
            int id = -1, dis = INT_MAX;
            min_dis(s, father, t, id, dis), min_dis(e, father, t, id, dis);
            res.push_back(id);
        }
        return res;
    }

    void min_dis(int v, int vf, int target, int& id, int& dis) {
        while(true) {
            int tf = lca(v, target);
            if(dis > depth[v] + depth[target] - 2 * depth[tf]) {
                dis = depth[v] + depth[target] - 2 * depth[tf];
                id = v;
            }
            if(v == vf) break;
            v = f[v][0];
        }
    }

    int get_ancestor(int v, int k){
        if(depth[v] < k) return -1;
        for(int j = 0; j < 31; j++) {
            if((1 << j) & k)
                v = f[v][j];
        }
        return v;
    }

    int lca(int x, int y) {
        if(depth[x] > depth[y]) swap(x, y);
        y = get_ancestor(y, depth[y] - depth[x]);
        if(x == y) return y;
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