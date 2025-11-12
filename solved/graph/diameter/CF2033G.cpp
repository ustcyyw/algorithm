/**
 * @Time : 2024/11/28-5:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2033G 2200 树的直径 lca
 */
 /*
  * 树的直径 树中任意一点到其它点的最大距离 一定是到直径的端点之一
  * （可以有多条直径 多个直径端点 但是只要找到其中一条的两个端点即可）
  * 本题对向上行走有限制 走到最高点w后 w子树中的任意一个点都可以到达
  * 那么v在w子树中能到的最大距离 就是w子树的直径的两端
  *
  * 如何找最高点w 就需要使用lca
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, q, depth[N], len[N], a[N], b[N], dis[N], node[N];
vector<vector<int>> graph, f;

void dfs1(int v, int father) {
    if(father != -1) depth[v] = depth[father] + 1;
    f[v][0] = father;
    for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
        f[v][j] = f[f[v][j - 1]][j - 1];
    for(int w : graph[v]) {
        if(w != father)
            dfs1(w, v);
    }
}
// 更新每个子数的直径及直径对应的两个端点
void dfs2(int v, int father) {
    if(father != -1 && graph[v].size() == 1) {
        len[v] = 0, a[v] = v, b[v] = v;
        dis[v] = 0, node[v] = v;
        return;
    }
    int d1 = -1, d2 = -1, n1 = -1, n2 = -1;
    for(int w : graph[v]) {
        if(w == father) continue;
        dfs2(w, v);
        // 看子树w的直径是否比当前记录的v的直径大
        if(len[v] < len[w]) len[v] = len[w], a[v] = a[w], b[v] = b[w];
        // 更新到叶子结点的最大深度和次大深度
        if(d1 < dis[w]) {
            d2 = d1, n2 = n1;
            d1 = dis[w], n1 = node[w];
        } else if(d2 < dis[w]) d2 = dis[w], n2 = node[w];
    }
    // 更新v到叶子结点的最大距离
    dis[v] = d1 + 1, node[v] = n1;
    // 更新树的直径
    int temp = d1 + 1 + d2 + 1;
    if(temp > len[v]) {
        len[v] = temp;
        a[v] = n1, b[v] = n2 == -1 ? v : n2;
    }
}

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

// 计算两个结点的距离
int cal(int v, int w) {
    int father = lca(v, w);
    return depth[v] - depth[father] + depth[w] - depth[father];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        graph.assign(n + 1, {});
        fill(len, len + n + 1, -1);
        f = vector(n + 1, vector(32, -1));
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(1, -1);
        dfs2(1, -1);
        cin >> q;
        for(int i = 1, v, k; i <= q; i++) {
            cin >> v >> k;
            int w = get_ancestor(v, min(k, depth[v] - depth[1])); // 先找向上距离为k的父亲结点
            cout << max(cal(v, a[w]), cal(v, b[w])) << " ";
        }
        cout << "\n";
    };
};