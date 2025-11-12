/**
 * @Time : 2025/2/19-12:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF652E 2300 tarjan 边双连通分量缩点 （sb题目有重边但没说）
 */
 /*
  * 设所求的两个结点x和y 画图发现
  * 如果x和y在同一个环内，那么他们就只能在环内走（简单环） 或者通过环上的其它环走出去再绕回来（多个环）
  * 那么环内有1的边，或者出去再绕回来的环上有1的边 就能达成条件；否则，不可以
  * 如果x和y不在同一个环内，但是会经过一些环，那么只要环内有1的边 就一定能选择走带1的那部分
  * 从而满足条件地从x到y
  * 因此 环成为一个重要的结构 而且由于路径只能只一遍的性质 走过一次的路径 相当于切割了这个图
  * 想到在无向图中 边双连通分量缩点
  * 缩点后的同一个分量中如果有1的边 就认为这个分量是1
  * （因此总能通过一条路径从分量中走过1的边 并且走出这个分量）
  *
  * 通过缩点后就变成树
  * 如果x和y在一个分量中 就看这个分量是否包含有1的边
  * 反之 则从x到y的过程中看是否经过含有1的分量、或者经过1的边
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, mod = 1e9 + 7;
ll T = 1e8, n, m, a[N], b[N], z[N], node1, node2, group[N], hasOne[N];
vector<vector<ll>> graph;
map<ll, int> dupE;
set<ll> bridge;

void tarjan() {
    vector<int> dfn(n + 1, -1), low(n + 1, INT_MAX);
    int time = 1;
    function<void(ll, int)> dfs = [&](ll v, int f) -> void {
        dfn[v] = low[v] = time++;
        for(ll w : graph[v]) {
            if(dfn[w] == -1) {
                dfs(w, v);
                low[v] = min(low[v], low[w]);
                if(low[w] > dfn[v]) {
                    ll key = min(v, w) * T + max(v, w);
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

vector<vector<vector<int>>> rebuild() {
    vector<bool> marked(n + 1, false);
    function<void(int, ll)> dfs = [&](int gid, ll v) -> void {
        marked[v] = true, group[v] = gid;
        for(ll w : graph[v]) {
            ll key = min(v, w) * T + max(v, w);
            if(!marked[w] && !bridge.count(key))
                dfs(gid, w);
        }
    };
    int gid = 0;
    for(int i = 1; i <= n; i++)
        if(!marked[i]) dfs(++gid, i);
    vector<vector<vector<int>>> G(gid + 1);
    for(int i = 1; i <= m; i++) {
        int v = a[i], w = b[i], gv = group[v], gw = group[w];
        if(gv == gw) {
            if(z[i] == 1) hasOne[gv] = 1;
        } else {
            G[gv].push_back({gw, (int)z[i]});
            G[gw].push_back({gv, (int)z[i]});
        }
    }
    return G;
}

bool solve() {
    tarjan();
    vector<vector<vector<int>>> G = rebuild();
    int sg = group[node1], tg = group[node2];
    if(sg == tg) return hasOne[sg]; // 在同一个连通分量
    // 重新建图后是一棵树 所以只要用f就能避免重复遍历
    function<bool(int, int, bool)> dfs = [&](int v, int f, bool flag) -> bool {
        if(hasOne[v]) flag = true;
        if(v == tg) return flag;
        for(auto& edge : G[v]) {
            int w = edge[0], t = edge[1];
            if(w != f) {
                if(dfs(w, v, flag | t)) return true;
            }
        }
        return false;
    };
    return dfs(sg, -1, false);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    graph.assign(n + 1, {});
    for(int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i] >> z[i];
        graph[a[i]].push_back(b[i]), graph[b[i]].push_back(a[i]);
        dupE[min(a[i], b[i]) * T + max(a[i], b[i])]++;
    }
    cin >> node1 >> node2;
    cout << (solve() ? "YES" : "NO");
};