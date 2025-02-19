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
//    cin >> T;
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