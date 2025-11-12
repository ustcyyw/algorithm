/**
 * @Time : 2024/4/13-5:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, tim, cc;
int weight[N], dfn[N] = {0}, low[N], color[N], nw[N], onSta[N], from[M], to[M], degree[N];
vector<int> graph[N];

void dfs(stack<int>& stack, int v) {
    dfn[v] = low[v] = ++tim;
    onSta[v] = 1, stack.push(v);
    for(int w : graph[v]) {
        if(dfn[w] == 0) {
            dfs(stack, w);
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
}

int dfs2(int v) {
    int res = 0;
    for(int w : graph[v])
        res = max(res, dfs2(w));
    return res + nw[v];
}

void solve() {
    tim = cc = 0;
    stack<int> stack;
    for(int i = 1; i <= n; i++)
        if(dfn[i] == 0) dfs(stack, i);
    // 将连通分量的权重合并到颜色表示的结点中
    for(int i = 1; i <= n; i++)
        nw[color[i]] += weight[i];
    // 重新建图
    memset(graph, {}, sizeof(graph));
    for(int i = 1; i <= m; i++) {
        int v = from[i], cv = color[v], w = to[i], cw = color[w];
        if(cv != cw) {
            graph[cv].push_back(cw);
            degree[cw]++;
        }
    }
    int ans = -1;
    for(int i = 1; i <= cc; i++) {
        if(degree[i] == 0)
            ans = max(ans, dfs2(i));
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> weight[i];
    for(int i = 1; i <= m; i++) {
        cin >> from[i] >> to[i];
        graph[from[i]].push_back(to[i]);
    }
    solve();
};