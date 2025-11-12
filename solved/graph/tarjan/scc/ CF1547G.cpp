/**
 * @Time : 2024/7/11-2:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1547G tarjan 有向图缩点 scc
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 4e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, ans[N], marked[N], dfn[N], low[N], color[N], onSta[N];
vector<vector<int>> graph, edges;
set<int> self;

void scc() {
    int cc = 0, time = 1; // 分别表示颜色和时间戳
    stack<int> stack;
    function<void(int)> dfs = [&](int v) -> void {
        dfn[v] = low[v] = ++time;
        onSta[v] = 1, stack.push(v);
        for(int w : graph[v]) {
            if(dfn[w] == -1) {
                dfs(w);
                low[v] = min(low[v], low[w]);
            } else if(onSta[w])
                low[v] = min(low[v], dfn[w]);
        }
        if(dfn[v] == low[v]) {
            color[v] = ++cc;
            int temp = -1, cnt = 0; // cnt记录此连通分量中的点的个数
            while(temp != v) {
                temp = stack.top();
                cnt++, color[temp] = cc; // 标记该结点的颜色
                onSta[temp] = 0, stack.pop();
            }
            if(cnt > 1 || self.count(v)) ans[cc] = 3; // 连通分量中不止一个点 或者有自环 表示有无限的路径
        }
    };
    dfs(1);
    // 重新建图 建反图
    graph.assign(n, {});
    for(auto& edge : edges) {
        int v = edge[0], cv = color[v], w = edge[1], cw = color[w];
        graph[cw].push_back(cv);
    }
}

int dfs(int v) {
    if(marked[v]) return ans[v];
    marked[v] = 1;
    if(ans[v] == 3) return 3;
    for(int w : graph[v]) {
        int t = dfs(w);
        if(t == 3) {
            ans[v] = 3;
            break;
        }
        if(t == 1) {
            if(ans[v] == 1 || ans[v] == 0)
                ans[v]++;
        } else if(t == 2) ans[v] = 2;
    }
    return ans[v];
}

void solve() {
    scc();
    int s = color[1];
    if(ans[s] != 3) ans[s] = 1, marked[s] = 1;
    for(int i = 1; i <= n; i++) {
        int t = dfs(color[i]);
        cout << (t == 3 ? -1 : t) << " ";
    }
    cout << "\n";
}

void init() {
    graph.assign(n + 1, {}), edges = {}, self = {};
    fill(ans, ans + n + 1, 0);
    fill(dfn, dfn + n + 1, -1);
    fill(onSta, onSta + n + 1, 0);
    fill(marked, marked + n + 1, 0);
    fill(low, low + n + 1, INT_MAX);
    fill(color, color + n + 1, 0);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        init();
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            if(v == w) self.insert(w);
            else edges.push_back({v, w}), graph[v].push_back(w);
        }
        solve();
    }
};