/**
 * @Time : 2024/4/20-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 无权树上任意一个节点，与它距离最远的节点一定是直径的某个端点（二个端点之一）
 * 那么在不破坏直径的情况下 任意一点的删除都可以得到该点为起点的最长路径值
 * 而只剩下直径之后 就是一个单链 可以任意顺序删除两端的结点
 *
 * 具体实现
 * 1. 先用一次dfs找到直径 并且标记直径的两个端点a b
 * 2. 在用一次dfs，并且将其中一个端点a设置为根结点，计算深度并且预处理lca
 * 于是某个结点i到达a的距离就是depth[i]，到达b的距离则先找到i和b的最近公共祖先v
 * d2 = depth[b] + d1 - 2 * depth[v]
 * 在dfs的过程中也标记哪些结点是直径中的 并且将直径路径存储在path中
 * 3.从叶子结点开始删除 所以需要使用拓扑排序来保证从叶子结点删除
 * 4.针对直径中的结点从边缘开始删除
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, d = 0, a, b, depth[N], f[N][32], ind[N], path[N], degree[N];
vector<int> graph[N];

// dfs找到直径 及相应的两个点
vector<int> dfs1(int v, int father) {
    int d1 = -1, n1 = -1, d2 = -1, n2 = -1;
    for(int w : graph[v]) {
        if(w == father) continue;
        vector<int> temp = dfs1(w, v);
        int d3 = temp[0], n3 = temp[1];
        if(d3 >= d1) {
            d2 = d1, d1 = d3;
            n2 = n1, n1 = n3;
        } else if(d3 > d2)
            d2 = d3, n2 = n3;
    }
    if(d2 == -1) {
        if(d1 + 1 > d) d = d1 + 1, a = v, b = n1;
    } else if(d1 + d2 + 2 > d)
        d = d1 + d2 + 2, a = n1, b = n2;
    if(d1 == -1) return {0, v};
    return {d1 + 1, n1};
}
// 以其中一个端点为根 计算到各个子结点的深度、预处理lca。并且标记在直径上的结点
void dfs2(int v, int father) {
    if(father != -1) depth[v] = depth[father] + 1;
    f[v][0] = father;
    for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
        f[v][j] = f[f[v][j - 1]][j - 1];
    for(int w : graph[v]) {
        if(w == father) continue;
        dfs2(w, v);
        if(ind[w]) {
            ind[v] = 1;
            path[v] = w; // 标记直径的路径
        }
    }
}

// 找到v的向上数的第k个祖先结点
int get_ancestor(int v, int k) {
    if(depth[v] < k) return -1;
    for(int j = 0; j < 31; j++) {
        if((1 << j) & k)
            v = f[v][j];
    }
    return v;
}

int lca(int x, int y) {
    if(depth[x] > depth[y]) swap(x, y); // 确保y比x深度更深
    y = get_ancestor(y, depth[y] - depth[x]); // 保证x和y同一深度
    if(x == y) return y;
    // 找到第一个不是它们祖先的两个点。
    for(int j = 30; j >= 0 && x != y; j--) {
        if(f[x][j] != f[y][j])
            x = f[x][j], y = f[y][j];
    }
    return f[x][0];
}

void solve() {
    dfs1(1, -1);
    ind[b] = 1;
    dfs2(a, -1);
    ll ans = 0;
    vector<vector<int>> res;
    // 先删除不在直径上的结点 要从叶子结点开始删 使用拓扑排序
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 1 && !ind[i]) queue.push(i);
    while (queue.size()) {
        int i = queue.front(); queue.pop();
        int v = lca(b, i);
        int d1 = depth[i], d2 = depth[b] + d1 - 2 * depth[v];
        ans += max(d1, d2);
        if(d1 >= d2) res.push_back({a, i, i});
        else res.push_back({b, i, i});
        for(int w : graph[i])
            if(--degree[w] == 1) queue.push(w);
    }
    // 删除在直径上的结点 优先保留b 从a这端开始删
    for(int x = a; x != b; x = path[x]) {
        ans += depth[b] - depth[x];
        res.push_back({x, b, x});
    }
    cout << ans << "\n";
    for(auto& p : res)
        cout << p[0] << " " << p[1] << " " << p[2] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
        degree[v]++, degree[w]++;
    }
    solve();
};