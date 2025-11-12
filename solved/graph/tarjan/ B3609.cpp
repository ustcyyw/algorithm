/**
 * @Time : 2024/1/2-5:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 强连通分量模板
 */
#include<bits/stdc++.h>
using namespace std;

int n, m;

vector<vector<int>> tarjan2(vector<vector<int>>& graph) {
    int time = 1;
    stack<int> stack;
    vector<int> dfn(n + 1, -1), low(n + 1, INT_MAX), onStack(n + 1, false);
    vector<vector<int>> groups; // 强连通分量
    function<void(int)> dfs = [&](int v) -> void {
        dfn[v] = low[v] = time++;
        onStack[v] = true, stack.push(v);
        for(int w : graph[v]) {
            if(dfn[w] == -1) { // w 还没被访问过，那么它是v的儿子
                dfs(w);
                low[v] = min(low[v], low[w]);
            } else if(onStack[w]) // w被访问过 该结点依旧存在于栈中 更新low[v]
                low[v] = min(low[v], dfn[w]);
        }
        if(dfn[v] == low[v]) {
            vector<int> temp;
            int t = -1;
            while(t != v) {
                t = stack.top(); stack.pop();
                onStack[t] = false, temp.push_back(t);
            }
            groups.push_back(temp);
        }
    };
    for(int i = 1; i <= n; i++)
        if(dfn[i] == -1) dfs(i);
    return groups;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w);
    }
    vector<vector<int>> groups = tarjan2(graph);
    for(auto& nodes : groups)
        sort(nodes.begin(), nodes.end());
    sort(groups.begin(), groups.end(), [](auto& a, auto& b) -> bool {return a[0] < b[0];});
    cout << groups.size();
    for(auto& nodes : groups) {
        cout << "\n";
        for(int& node : nodes)
            cout << node << " ";
    }
}