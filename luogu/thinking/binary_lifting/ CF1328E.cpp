/**
 * @Time : 2024/6/21-9:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1328E 倍增-lca 贪心
 */
/*
  * 最深的点d_node 那条路径必须到这个点
  * 其它点v到这条路径的最近点就是lca(d_node, v)
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, T = 1e6;
typedef long long ll;
int n, q, m, depth[N], f[N][32], md, d_node;
vector<int> graph[N], nodes;

void dfs(int v, int father) {
    if(father != -1) depth[v] = depth[father] + 1;
    f[v][0] = father;
    for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
        f[v][j] = f[f[v][j - 1]][j - 1];
    for(int w : graph[v]) {
        if(w != father)
            dfs(w, v);
    }
};

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

bool check() {
    for(int v : nodes) {
        int father = lca(v, d_node);
        if(depth[v] - depth[father] > 1) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> q;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs(1, -1);
    while(q-- > 0) {
        cin >> m;
        nodes.assign(m, 0);
        md = -1;
        for(int i = 0; i < m; i++) {
            cin >> nodes[i];
            if(depth[nodes[i]] > md) md = depth[nodes[i]], d_node = nodes[i];
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
};