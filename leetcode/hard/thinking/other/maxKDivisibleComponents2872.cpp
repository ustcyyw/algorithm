/**
 * @Time : 2023/10/1-12:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 假设一个结点及其子结点之和能被k整除 和记为ik
 * 它就应该和它父亲结点断开 分成两个部分
 * 因为如果这棵子树参与到其父亲的部分 一起的和能被k整除，和为 jk
 * 那么将其断开后，其父亲的另外的部分之和就是 (j - i)k 也能被k整除 因此分开一定更好
 *
 * 在dfs中 如果发现某一个子树之和能被k整除，就将其和设置为0
 * 这样其父亲就计算和的时候就忽略了它 从而实现了断开的效果
 */
class Solution {
public:
    vector<int> sum, cnt, values;
    vector<vector<int>> graph;
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        this->values = values;
        sum.assign(n, 0), cnt.assign(n, 0);
        graph.assign(n, {});
        for(auto& edge : edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(0, -1, k);
        return cnt[0];
    }

    void dfs(int v, int f, int k) {
        int cs = values[v], cc = 0;
        for(int w : graph[v]) {
            if(w == f) continue;
            dfs(w, v, k);
            cs += sum[w], cc += cnt[w];
        }
        if(cs % k == 0)
            cc++, cs = 0;
        cnt[v] = cc, sum[v] = cs;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}