/**
 * @Time : 2024/1/4-9:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 点双连通分量 模版
 */
/*
 * 回到tarjan算法中 dfs搜索树的本质
 * 在dfs中如果发现 low[w] >= dfn[v] 说明v是割点
 * 并且去掉v后 w及其子孙结点都无法回溯到x和x的祖先 那么他们在另外一个点双连通分量（bcc）中
 * 因此一旦发现有 low[w] >= dfn[v] 就应当将w及其子孙放入一个bcc 并且要将v也放进去
 * 可以使用栈来维护w及其子孙
 * 注意：
 * w的子孙中 可能有一部分已经在别的bcc中了 但那一部分已经在更早些时候出栈了
 * 不会放到当前找到的bcc中
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n, m, idx, st[N];
vector<vector<int>> graph;

void tarjan(vector<vector<int>>& groups) {
    vector<int> dfn(n + 1, -1), low(n + 1, INT_MAX);
    int time = 1;
    function<void(int, int)> dfs = [&](int v, int f) -> void {
        int cnt = 0;
        dfn[v] = low[v] = time++;
        st[idx++] = v;
        for(int w : graph[v]) {
            if(dfn[w] == -1) {
                cnt++, dfs(w, v);
                low[v] = min(low[v], low[w]);
                if(low[w] >= dfn[v]) {
                    vector<int> temp;
                    // 注意 idx - 1才是栈顶索引，st[idx] == w 说明w刚好出栈 并且割点没有出栈
                    while(st[idx] != w)
                        temp.push_back(st[--idx]);
                    temp.push_back(v); // 点双是包括割点的
                    groups.push_back(temp);
                }
            } else if(w != f)
                low[v] = min(low[v], dfn[w]);
        }
        if(cnt == 0 && f == -1) groups.push_back({v}); // 特判孤立点
    };
    for(int i = 1; i <= n; i++) {
        if(dfn[i] == -1) {
            idx = 0; dfs(i, -1);
        }
    }
}

void solve() {
    vector<vector<int>> groups;
    tarjan(groups);
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
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
}