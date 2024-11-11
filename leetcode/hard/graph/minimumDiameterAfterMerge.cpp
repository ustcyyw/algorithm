/**
 * @Time : 2024/6/30-3:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛404 t4 树的直径
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 容易想到枚举两树的连接点 连接之后的直径只有2种可能
     * 1.原本两树中的直径
     * 2.两个连接点到原本树中的最远距离和 + 1
     * 对于第二种情况 某个点到树中的最远距离 一定是该点到直径端点(a和b) t = max(d1, d2)
     * 那么要让合并之后的树直径最小 应该要找到最小的t1和最小的t2 于是不用暴力枚举
     * 只需要在两树中分别找到让t最小的结点即可。
     * 假设点v在直径上 显然为了让max(d1, d2) 这个点应该取直径的中点
     * 假设点v不在直径上 由于这是一颗树 这个点到直径端点的路径一定是要先经过直径上某点u
     * 因此d1 = dis(v, a) = dis(v, u) + dis(u, a), d2 = dis(v, b) = dis(v, u) + dis(u, a)
     * max(d1, d2) > max(dis(u, a), dis(u, a))
     * 因此点v不到直径上 他所计算出来的t一定比在直径上的点大
     * 于是得出结论 两棵树中用于连接的点是直径的中点 没有必要知道具体是哪个结点
     * 显然这个中点对应的max(d1, d2)就是直径长度的一半 向上取整
     */
    int get_diameter(vector<vector<int>> &edges) {
        int n = edges.size() + 1, d = 0;
        if(n == 1) return 0;
        vector<vector<int>> graph(n);
        for (auto &edge: edges) {
            int v = edge[0], w = edge[1];
            graph[v].push_back(w), graph[w].push_back(v);
        }
        // dfs找到直径 及相应的两个点
        function<int(int, int)> dfs = [&](int v, int father) -> int {
            int d1 = -1, d2 = -1;
            for (int w: graph[v]) {
                if (w == father) continue;
                int d3 = dfs(w, v);
                if (d3 >= d1) d2 = d1, d1 = d3;
                else if (d3 > d2) d2 = d3;
            }
            if (d2 == -1) d = max(d, d1 + 1);
            else d = max(d, d1 + d2 + 2);
            if (d1 == -1) return 0;
            else return d1 + 1;
        };
        dfs(0, -1);
        return d;
    }

    int minimumDiameterAfterMerge(vector<vector<int>> &edges1, vector<vector<int>> &edges2) {
        int d1 = get_diameter(edges1), d2 = get_diameter(edges2);
        int t1 = (d1 + 1) / 2 + (d2 + 1) / 2 + 1;
        return max({t1, d1, d2});
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}