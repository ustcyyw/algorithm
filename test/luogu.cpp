/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
int T, n, f[N], dfn[N], low[N], color[N], onSta[N], cr[N], degree[N];
vector<vector<int>> ans, graph;

void scc() {
    int cc = 0, time = 1; // 分别表示颜色和时间戳
    stack<int> stack;
    function<void(int)> dfs = [&](int v) -> void {
        dfn[v] = low[v] = ++time;
        onSta[v] = 1, stack.push(v);
        int w = f[v];
        if(dfn[w] == 0) {
            dfs(w);
            low[v] = min(low[v], low[w]);
        } else if(onSta[w])
            low[v] = min(low[v], dfn[w]);
        if(dfn[v] == low[v]) {
            color[v] = ++cc;
            int temp = -1;
            while(temp != v) {
                temp = stack.top();
                color[temp] = cc, cr[cc] = temp; // 标记该结点的颜色，也记录该颜色中的一个结点
                onSta[temp] = 0, stack.pop();
            }
        }
    };
    for(int i = 1; i <= n; i++)
        if(dfn[i] == 0) dfs(i);
    // 重新建图
    graph.assign(cc + 1, {});
    for(int v = 1; v <= n; v++) {
        int cv = color[v], w = f[v], cw = color[w];
        if(cv != cw)
            graph[cv].push_back(cw), degree[cw]++;
    }
}

void dfs(vector<int>& ids, int v) {
    if(graph[v].empty())
        ids[v] = v;
    for(int w : graph[v]) {
        if(ids[w] == -1)
            dfs(ids, w);
        ids[v] = ids[w];
    }
}

void solve() {
    scc();
    int m = graph.size();
    if(m == 2) { // 原图缩点后只有一个结点 那么不用添加任何边了
        cout << 0;
        return;
    }
    vector<int> ids(m, -1);
    map<int, vector<int>> part;
    for(int c = 1; c < m; c++) {
        if(degree[c] > 0 || ids[c] != -1) continue;
        dfs(ids, c);
        int cn = cr[c], rootN = cr[ids[c]];
        part[rootN].push_back(cn);
    }
    vector<vector<int>> aux;
    for(auto& [rootN, arr] : part) {
        while(arr.size() > 1) {
            ans.push_back({rootN, arr.back()});
            arr.pop_back();
        }
        aux.push_back({rootN, arr.back()});
    }
    for(int i = 0; i < aux.size() - 1; i++)
        ans.push_back({aux[i][0], aux[i + 1][1]});
    ans.push_back({aux.back()[0], aux[0][1]});
    cout << ans.size() << "\n";
    for(auto& p : ans)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> f[i];
        solve();
    }
};