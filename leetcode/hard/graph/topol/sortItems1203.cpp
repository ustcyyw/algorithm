/**
 * @Time : 2023/4/20-2:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int super_source = INT_MAX;
class Graph {
public:
    unordered_map<int, unordered_set<int>> graph;
    unordered_map<int, int> degree; // 计算入度
    void add(int v, int w) {
        check(v), check(w);
        if (graph[v].count(w)) return; // 不加入重复边
        graph[v].insert(w), degree[w]++;
    }

    void check(int v) {
        if (!graph.count(v)) graph[v] = {};
        if (!degree.count(v)) degree[v] = 0;
    }

    vector<int> topol_sort() {
        vector<int> res;
        queue<int> queue;
        queue.push(super_source);
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            if (v != super_source) res.push_back(v);
            for (int w: graph[v])
                if (--degree[w] == 0) queue.push(w);
        }
        // 除开超级源点，已排序的点不足图中全部点 说明不存在拓扑序
        if (res.size() < graph.size() - 1) return {};
        return res;
    }
};

class Solution {
public:
    /*
     * 组和组之间有拓扑关系
     * 组内也有拓扑关系
     *
     * 先确定组之间的排序 让同一组的元素拓扑排序后 放在一起
     *
     * 有一些组之间，或者同组元素之间没有做前置任务要求，也不是别人的前置任务
     * 这样的组或者元素，在拓扑序中可以放在任意位置
     * 为了方便处理这种特殊情况 引入一个超级源点 该点是所有点的前置任务
     */
    vector<int> sortItems(int n, int m, vector<int> &group, vector<vector<int>> &beforeItems) {
        for (int i = 0; i < n; i++) // 重新编辑组号 方便分组
            group[i] = group[i] >= 0 ? group[i] + 1 : -i;
        // group id --> Graph 组内相邻 但也可能有拓扑序列 记录每一个组的图
        unordered_map<int, Graph> graphs;
        // 组与组之间构成的图
        Graph groupG;
        for (int w = 0; w < n; w++) {
            int wg = group[w];
            groupG.add(super_source, wg);
            graphs[wg].add(super_source, w);
            for (int v: beforeItems[w]) {
                int vg = group[v];
                if (vg != wg) groupG.add(group[v], wg); // 组别之间具有先后顺序
                else {
                    if (!graphs.count(vg)) graphs[vg] = Graph();
                    graphs[vg].add(v, w);
                }
            }
        }
        vector<int> group_topol = groupG.topol_sort();
        if (group_topol.empty()) return {};
        vector<int> res;
        for (int group_id: group_topol) {
            if (group_id < 0) res.push_back(-group_id);
            else {
                vector<int> temp = graphs[group_id].topol_sort();
                if (temp.empty()) return {};
                for (int num: temp) res.push_back(num);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}