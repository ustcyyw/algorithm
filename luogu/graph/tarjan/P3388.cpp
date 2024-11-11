/**
 * @Time : 2024/1/2-5:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 割点模版
 */
#include<bits/stdc++.h>
using namespace std;

int n, m;

vector<int> tarjan1(vector<vector<int>>& graph) {
    int time = 1;
    vector<int> node, dfn(n, -1), low(n, INT_MAX);
    function<void(int, int)> dfs = [&](int v, int f) -> void {
        dfn[v] = low[v] = time++;
        int cnt = 0, l = 0; // cnt：儿子结点个数; l：v的儿子中最大的low[son]
        for(int w : graph[v]) {
            if(dfn[w] == -1) { // w 还没被访问过，那么它是v的儿子
                cnt++, dfs(w, v);
                l = max(l, low[w]);
                low[v] = min(low[v], low[w]);
            } else if(w != f) // w被访问过 且不是父结点 更新low[v]
                low[v] = min(low[v], dfn[w]);
        }
        if(f == -1 && cnt >= 2) node.push_back(v); // v是根 且在搜索树中有2个及以上的儿子
        if(f != -1 && cnt && l >= dfn[v]) node.push_back(v); // v不是根有儿子，且存在low[x_son] >= dfn[x]
    };
    for(int i = 1; i <= n; i++)
        if(dfn[i] == -1) dfs(i, -1);
    return node;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    vector<int> nodes = tarjan1(graph);
    sort(nodes.begin(), nodes.end());
    cout << nodes.size() << endl;
    for(int node : nodes)
        cout << node << " ";
}