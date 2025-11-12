/**
 * @Time : 2024/5/6-8:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 倍增 lca 最小生成树mst
 */

/*
 * 最小生成树的题 一般都先将mst构建出来 再考虑如何使用性质
 * 可以考虑非树边后形成环 环有什么性质
 *
 * 最小生成树
 * 1.它首先是一棵树 加上任意一个非树边e1（权重w1） 肯定会得到一个环
 * 在这个环中 去掉其它一条边e2（权重w2）可以恢复成一棵树
 * 如果 w2 < w1 新树就不是最小生成树
 * 因此要保持最小生成树 去掉的边应该满足 w2 == w1
 * 2.另一方面 e1是非树边 说明在这个环中w1是最大权重 因为如果w1不是最大权重
 * 那么去掉权重更大的那条边得到的生成树权重更小 就与最小生成树矛盾
 *
 * 因而 只有在添加非树边后得到的环中存在和它权重相同的边，mst才不唯一
 * 并且这个权重就是环中最大权，只需要将非树边权重+1即可避免mst不唯一
 *
 * 先构建出mst，标记出树边
 * 枚举非树边(u--v) 假定形成了一个环 找该环中是否有等于该边权重的其他边
 * 也就是找该环中树边的最大权重 看是否相等
 * u和v是树中两点 其公共祖先为x 那么u--x，v--x两条路径上的最大权重就是要找的答案
 * 可以使用倍增的思想，lca来快速查找
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, id[N], marked[N], depth[N], f[N][32], pm[N][32];
vector<vector<int>> edges;
vector<vector<int>> graph[N];

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

bool connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return false;
    id[p] = q;
    return true;
}

void kruskal() {
    for(auto& edge : edges) {
        int w = edge[0], u = edge[1], v = edge[2];
        if(connect(u, v)) {
            marked[edge[3]] = 1;
            graph[v].push_back({w, u}), graph[u].push_back({w, v});
        }
    }
}
// 倍增预处理
void dfs(int v, int father, int val) {
    depth[v] = father == -1 ? 0 : depth[father] + 1;
    f[v][0] = father;
    if(father != -1) pm[v][0] = val;
    for(int i = 1; i < 32 && f[v][i - 1] != -1; i++) {
        int w = f[v][i - 1];
        f[v][i] = f[w][i - 1];
        pm[v][i] = max(pm[v][i - 1], pm[w][i - 1]);
    }
    for(auto& edge : graph[v]) {
        if(edge[1] == father) continue;
        dfs(edge[1], v, edge[0]);
    }
}

int getKthAncestor(int node, int k, int& val){
    for(int i = 0; i < 31; i++){
        if(((1 << i) & k) > 0) {
            val = max(val, pm[node][i]);
            node = f[node][i];
        }
    }
    return node;
}
// 找公共祖先的同时 找到两条路径上的最大权重
int lca(int x, int y){
    if(depth[x] > depth[y]) swap(x, y); // 保证y更深
    int val = 0;
    y = getKthAncestor(y, depth[y] - depth[x], val); // 保证x和y同一深度
    if(x == y) return val;
    // 找到第一个不是它们祖先的两个点。
    for (int j = 30; j >= 0 && y != x; --j) {
        if (f[x][j] != f[y][j]) {
            val = max(val, max(pm[x][j], pm[y][j]));
            x = f[x][j], y = f[y][j];
        }
    }
    return max(val, max(pm[x][0], pm[y][0]));
}

void solve() {
    kruskal();
    dfs(1, -1, -1);
    int ans = 0;
    for(auto& edge : edges) {
        if(marked[edge[3]]) continue;
        int weight = edge[0], val = lca(edge[1], edge[2]);
        if(weight == val) ans++;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        id[i] = i;
    for(int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        edges.push_back({w, u, v, i});
    }
    sort(edges.begin(), edges.end());
    solve();
};