/**
 * @Time : 2024/5/19-8:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1213F 缩点 拓扑排序
 */
 /*
  * p和q两个序列都规定特定位置的字符的大小关系
  * 大小关系类比于优先级 那么就可以构建有图 p[i] -> p[i+1],q[i] -> q[i + 1]
  * 然后发现有一些不等式传递关系会成环 比如题目给的例子
  * 成环就是强连通分量 要使不等式成立 那么这些结点代表的字符就必须是相同的
  * 因此想到了将等价的结点设置为一个结点 缩点
  * 经过缩点之后就是有向无环图 字符的大小关系就是优先级
  * 然后题目要求最少有个k个不同的字符 因此每个不同优先级的结点都应该安排不一样的字符
  * 直到已经有k个不同字符了 那么剩下的全部安排z即可。当然如果没凑够k个字符 就说明没办法完成构造
  *
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, n, k, cc = 0, tim = 1;
int p[N], q[N], dfn[N], low[N], onStack[N], color[N];
vector<int> rc[N]; // 某个颜色对应的原始结点有哪些
vector<unordered_set<int>> graph;
string s;


void init_build(int *a) {
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(i != 1) graph[a[i - 1]].insert(a[i]);
    }
}

void re_build(int *a) {
    for(int i = 2; i <= n; i++) {
        int v = a[i - 1], cv = color[v], w = a[i], cw = color[w];
        if(cv != cw) graph[cv].insert(cw);
    }
}

void scc() {
    stack<int> stack;
    function<void(int)> dfs = [&](int v) -> void {
        dfn[v] = low[v] = ++tim;
        onStack[v] = 1, stack.push(v);
        for(int w : graph[v]) {
            if(dfn[w] == 0) {
                dfs(w);
                low[v] = min(low[v], low[w]);
            } else if(onStack[w])
                low[v] = min(low[v], dfn[w]);
        }
        if(dfn[v] == low[v]) {
            color[v] = ++cc;
            int temp = -1;
            while(temp != v) {
                temp = stack.top();
                color[temp] = cc, rc[cc].push_back(temp); // 标记该结点的颜色
                onStack[temp] = 0, stack.pop();
            }
        }
    };
    for(int i = 1; i <= n; i++)
        if(dfn[i] == 0) dfs(i);
    // 重新建图
    graph.assign(cc + 1, {});
    re_build(p), re_build(q);
}

bool topol_bfs() {
    vector<int> ans, degree(cc + 1, 0);
    for(int v = 1; v <= cc; v++) {
        for(int w : graph[v])
            degree[w]++;
    }
    queue<int> queue;
    for(int i = 1; i <= cc; i++)
        if(degree[i] == 0) queue.push(i);
    int kk = 0;
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        char character = (char)(kk + 'a');
        for(int idx : rc[v])
            s[idx] = character;
        kk++;
        if(kk == k) break; // 后续默认都是z即可
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
    return kk == k;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    graph.assign(n + 1, {});
    init_build(p), init_build(q);
    scc();
    s.assign(n + 1, 'z');
    if(topol_bfs()) {
        cout << "YES\n";
        cout << s.substr(1);
    } else cout << "NO";
};