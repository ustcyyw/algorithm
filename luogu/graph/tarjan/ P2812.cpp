/**
 * @Time : 2024/4/15-3:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 原始是有向图 可能有强连通分量 强连通分量里的机器可以互相
 * 有多少个入度为0的点 就需要多少个母机
 * 因为只有设置这台机器为母机才能让它使用软件 其它入度非0的机器都可以靠别人传输
 *
 * 问题2：任意机器作为母机都要能传遍所有机器
 * 选择入度不为0的机器 要能传到入度为0度机器 就得找个机器连一条线过去
 * 而选择出度为0的机器 要让它传给其它机器 就得让他连一个线到别的机器
 * 那么最好的办法就是让出度为0的机器去连入度为0的机器
 * 所以需要连多少条线 就取决于 入度为0度机器个数，出度为0的机器个数 二者取最大
 * 注意 如果有且仅有一个连通分量 那么不需要任何连线就满足问题2的要求 直接输出0
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, tim, cc;
int dfn[N] = {0}, low[N], color[N], onSta[N], from[M], to[M], in[N], out[N];
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

void solve() {
    tim = cc = 0;
    for(int i = 1; i <= n; i++)
        if(dfn[i] == 0) dfs(i);
    // 缩点 重新建图 重新建图后不再存在强连通分量
    memset(graph, {}, sizeof(graph));
    for(int i = 1; i <= m; i++) {
        int v = from[i], cv = color[v], w = to[i], cw = color[w];
        if(cv != cw) {
            graph[cv].push_back(cw);
            out[cv]++, in[cw]++;
        }
    }
    int cnt1 = 0, cnt2 = 0;
    for(int i = 1; i <= cc; i++) {
        // 入度为0 找到一个新的起点 要设置这台机器为母机才能让它使用软件
        if(in[i] == 0) cnt1++;
        if(out[i] == 0) cnt2++;
    }
    cout << cnt1 << "\n";
    if(cc == 1) cout << 0; // 有且仅有一个连通分量的情况
    else cout << max(cnt1, cnt2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    m = 0;
    for(int i = 1; i <= n; i++) {
        int num;
        while(true) {
            cin >> num;
            if(num == 0) break;
            m++;
            graph[i].push_back(num);
            from[m] = i, to[m] = num;
        }
    }
    solve();
};