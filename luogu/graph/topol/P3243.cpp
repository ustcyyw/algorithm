/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

/*
 * 有先后关系 显然和拓扑序有关
 * 但是要求在满足先后关系的情况下，编号小的排在前面
 * 容易想到贪心
 * 如果正着，每次先排当前编号最小的 会出现错误
 * 比如某个编号最大的，其后置有编号最小的，但没有先选它
 * 比如
 * 5 -> 1
 * 4 -> 3
 * 如果先排当前编号最小的，顺序则为4351
 * 如果先排了5，顺序为5143 显然更优
 *
 * 不妨逆向思考 让编号大的排在后面 比 编号稍小的排在后面 至少不会差
 * 直觉上可以逆向贪心
 * 证明：
 * 按照题意模拟 每一次应该将还未排序最小编号 min_id 选出来
 * 然后将其前置结点的最优序列排好后 紧接着放置min_id
 * 经过上述操作 将min_id及其前置排序完成。
 * 剩余未排序的结点 一定是min_id的后置结点
 * 按照拓扑排序的规则，剩余结点本就排在min_id后面
 * 根据题目要求 与min_id没有依赖关系的结点，由于编号比min_id大，也排在min_id后
 * 因此 剩余未排序的结点 又回到了相同的问题（子问题）
 * 于是得到结论 排在最后的结点 是拓扑关系中的出度为0的编号最大的结点
 *
 * 于是 我们可以在逆向图的拓扑排序中 采用最大编号贪心
 * 得到逆向图的最优拓扑排序后，再倒叙就得到正向图的最优解
 *
 * 注意 输出不能有多余空格
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int t, n, m, degree[N];
vector<vector<int>> graph;

vector<int> topol_sort() {
    vector<int> ans;
    priority_queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.top(); queue.pop();
        ans.push_back(v);
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
    return ans;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n >> m;
        fill(degree, degree + n + 1, 0);
        graph.assign(n + 1, {});
        for(int j = 1, v, w; j <= m; j++) {
            cin >> v >> w;
            graph[w].push_back(v), degree[v]++;
        }
        vector<int> order = topol_sort();
        if(order.size() != n) cout << "Impossible!" << endl;
        else {
            reverse(order.begin(), order.end());
            // 注意 输出不能有多余空格
            for(int j = 0, sz = order.size(); j < sz; j++) {
                if(j != sz - 1) cout << order[j] << " ";
                else cout << order[j] << endl;
            }
        }
    }
}