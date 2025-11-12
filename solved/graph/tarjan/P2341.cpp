/**
 * @Time : 2024/4/15-2:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 有向图 并且喜欢的关系是可以传递的 如果这是一个无环图 显然拓扑的终点才可能是答案
 * 但是本题的喜欢关系是可能成环的 强连通分量中的每一头牛都互相喜欢 因此可以缩点
 * 缩点之后变为有向无环图
 * 如果进行反向建图 可以认为子结点喜欢父节点
 * 那么 只有出度为0才可能是答案 并且只能后一个。
 * 因为如果有两个 就说明有两个分量
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, tim, cc;
int dfn[N] = {0}, low[N], color[N], onSta[N], from[M], to[M], degree[N];
vector<int> graph[N];
stack<int> stk;

void dfs(int v) {
    dfn[v] = low[v] = ++tim;
    onSta[v] = 1, stk.push(v);
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
            temp = stk.top();
            color[temp] = cc; // 标记该结点的颜色
            onSta[temp] = 0, stk.pop();
        }
    }
}

int solve() {
    tim = cc = 0;
    for(int i = 1; i <= n; i++)
        if(dfn[i] == 0) dfs(i);
    // 缩点 重新建图 重新建图后不再存在强连通分量
    memset(graph, {}, sizeof(graph));
    for(int i = 1; i <= m; i++) {
        int v = from[i], cv = color[v], w = to[i], cw = color[w];
        if(cv != cw) {
            graph[cw].push_back(cv); // 反向建图 于是可以认为子结点喜欢父节点
            degree[cv]++;
        }
    }
    int ac = -1;
    for(int i = 1; i <= cc; i++) {
        // 只有出度为0才可能是答案 并且只能后一个。因为如果有两个 就说明有两个分量
        if(degree[i] == 0) {
            if(ac != -1) return 0;
            ac = i;
        }
    }
    int cnt = 0;
    for(int i = 1; i <= n && ac != -1; i++)
        if(color[i] == ac) cnt++;
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> from[i] >> to[i];
        graph[from[i]].push_back(to[i]);
    }
    cout << solve();
};