/**
 * @Time : 2025/10/15-16:38
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3710 2163 二分 图论 2-sat
 */
 /*
  * 最小值最大，标准的二分答案的做法。关键是怎么写check函数呢？
  * 没有想到二分图的思路，想了并查集（因为有矛盾关系），但是也有地方没想明白。
  * 莫名其妙的想到了，这些点只能分在两个数组中，就相当于这些点的值为0或者1，代表在数组1或者数组2。
  * 能完成分组就代表着这些点的值要么是1，要么是0，没有矛盾。
  * 刚好2-sat就是可以解决有逻辑约束条件下，一组2元变量的赋值问题（是否可以完成赋值，可以的话各个变量到底是0还是1呢？）。
  * 套用2-sat的模板，本题中变量就是指各个point，赋值0就是放在数组1，赋值1就是放在数组2，
  * 逻辑约束就是固定最小距离为d的情况下，两个点i,j之间的距离dis(i,j) < d，那么这两个点就不可以在一个组里面。
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m;
    vector<int> dfn, low, color, onSta;
    vector<vector<int>> graph;
    int maxPartitionFactor(vector<vector<int>>& points) {
        n = points.size(), m = 2 * n;
        if(n == 2) return 0;
        int lo = 0, hi = 4e8;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if(check(points, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<vector<int>>& p, int d) {
        graph.assign(m, {});
        dfn.assign(m, 0), low.assign(m, 0), color.assign(m, 0), onSta.assign(m, 0);
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int dis = abs(p[i][0] - p[j][0]) + abs(p[i][1] - p[j][1]);
                if(dis >= d) continue;
                graph[i].push_back(j + n), graph[j].push_back(i + n);
                graph[i + n].push_back(j), graph[j + n].push_back(i);
            }
        }
        scc();
        for(int i = 0; i < n; i++) {
            if(color[i] == color[i + n]) return false;
        }
        return true;
    }

    void scc() {
        int cc = 0, time = 1; // 分别表示颜色和时间戳
        stack<int> stack;
        function<void(int)> dfs = [&](int v) -> void {
            dfn[v] = low[v] = ++time;
            onSta[v] = 1, stack.push(v);
            for(int w : graph[v]) {
                if(dfn[w] == 0) {
                    dfs(w);
                    low[v] = min(low[v], low[w]);
                } else if(onSta[w])
                    low[v] = min(low[v], dfn[w]);
            }
            if(dfn[v] == low[v]) {
                color[v] = ++cc;
                int temp = -1;
                while(temp != v) {
                    temp = stack.top();
                    color[temp] = cc; // 标记该结点的颜色
                    onSta[temp] = 0, stack.pop();
                }
            }
        };
        for(int i = 0; i < n; i++)
            if(dfn[i] == 0) dfs(i);
    }
};