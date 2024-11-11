/**
 * @Time : 2024/4/14-11:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 一个直观的想法是 在图中 入度为0且不是首都的结点 肯定首都现在没法直达的
  * 这样的结点都需要建一条路
  * 但是还会有一些强连通分量 分量中各个结点的入度都 > 0，但是首都可能没有路到达这些分量
  * 一旦首都能到达强连通分量中的一个点 这个分量中所有点也就可以到达了
  * 所有想到先在有向图中进行缩点 scc
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, s, tim, cc;
int dfn[N] = {0}, low[N], color[N], onSta[N], from[M], to[M], degree[N];
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

void solve() {
    tim = cc = 0;
    stack<int> stack;
    for(int i = 1; i <= n; i++)
        if(dfn[i] == 0) dfs(stack, i);
    // 缩点 重新建图 重新建图后不再存在强连通分量
    memset(graph, {}, sizeof(graph));
    for(int i = 1; i <= m; i++) {
        int v = from[i], cv = color[v], w = to[i], cw = color[w];
        if(cv != cw) {
            graph[cv].push_back(cw);
            degree[cw]++;
        }
    }
    // 缩点后 入度为0的点且它又不是首都 那么它一定不能从首都到达 就需要建一条路
    // 注意缩点后 等价结点是颜色编号 判断是否为首都也需要使用颜色去判断
    int ans = 0;
    for(int i = 1; i <= cc; i++) {
        if(color[s] != i && degree[i] == 0)
            ans++;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> s;
    for(int i = 1; i <= m; i++) {
        cin >> from[i] >> to[i];
        graph[from[i]].push_back(to[i]);
    }
    solve();
};