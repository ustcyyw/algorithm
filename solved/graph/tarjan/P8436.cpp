/**
 * @Time : 2024/1/2-9:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : tarjan 解决边双连通分量 （无向图）
 */
#include<bits/stdc++.h>
using namespace std;
const long long T = 1e8;
int n, m;
unordered_map<long long, int> dupE;
unordered_set<long long> bridge;
vector<vector<int>> graph;

void tarjan() {
    vector<int> dfn(n + 1, -1), low(n + 1, INT_MAX);
    int time = 1;
    function<void(int, int)> dfs = [&](int v, int f) -> void {
        dfn[v] = low[v] = time++;
        for(int w : graph[v]) {
            if(dfn[w] == -1) {
                dfs(w, v);
                low[v] = min(low[v], low[w]);
                if(low[w] > dfn[v]) {
                    long long key = min(v, w) * T + max(v, w);
                    if(dupE[key] == 1)
                        bridge.insert(key);
                }
            } else if(w != f)
                low[v] = min(low[v], dfn[w]);
        }
    };
    for(int i = 1; i <= n; i++)
        if(dfn[i] == -1) dfs(i, -1);
}

void solve() {
    vector<bool> marked(n + 1, false);
    function<void(vector<int>&, int)> dfs = [&](vector<int>& nodes, int v) -> void {
        marked[v] = true;
        nodes.push_back(v);
        for(int w : graph[v]) {
            if(!marked[w] && !bridge.count(min(v, w) * T + max(v, w)))
                dfs(nodes, w);
        }
    };
    vector<vector<int>> groups;
    for(int i = 1; i <= n; i++) {
        if(marked[i]) continue;
        vector<int> temp;
        dfs(temp, i);
        groups.push_back(temp);
    }
    cout << groups.size();
    for(auto& nodes : groups) {
        cout << "\n" << nodes.size() << " ";
        for(int& node : nodes)
            cout << node << " ";
    }
}

int main(){
    cin >> n >> m;
    graph.assign(n + 1, {});
    dupE.clear();
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
        dupE[min(v, w) * T + max(v, w)]++;
    }
    tarjan();
    solve();
}