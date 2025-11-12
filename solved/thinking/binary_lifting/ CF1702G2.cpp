/**
 * @Time : 2024/6/6-10:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1702G2 CF1702G1 lca + 观察树形
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, q, m, order[N], depth[N], tim = 0, f[N][32], nodes[N];
vector<int> graph[N];

void dfs1(int v, int father) {
    order[v] = ++tim;
    for(int w : graph[v]) {
        if(w == father) continue;
        dfs1(w, v);
    }
}

void lca(int s) {
    function<void(int, int)> dfs = [&](int v, int father) {
        if(father != -1) depth[v] = depth[father] + 1;
        f[v][0] = father;
        for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
            f[v][j] = f[f[v][j - 1]][j - 1];
        for(int w : graph[v]) {
            if(w != father)
                dfs(w, v);
        }
    };
    dfs(s, -1);
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

bool check() {
    int o1 = INT_MAX, o2 = INT_MIN, n1 = -1, n2 = -1;
    for(int i = 1, node; i <= m; i++) {
        cin >> node;
        nodes[i] = node;
        if(order[node] < o1) o1 = order[node], n1 = node;
        if(order[node] > o2) o2 = order[node], n2 = node;
    }
    // dfs序号最小和最大的两个点的lca 就是答案为yes时 路径的根结点
    int root = lca(n1, n2);
    n1 = -1, n2 = -1;
    for(int i = 1; i <= m; i++) {
        int node = nodes[i];
        if(node == root) continue;
        if(n1 == -1) n1 = node; // 确定从根出发的一条边
        else {
            int f1 = lca(n1, node);
            if(f1 != n1 && f1 != node) { // node 和n1不在同一条边上
                if(n2 == -1) n2 = node; // 确定第二条边
                else {
                    int f2 = lca(n2, node);
                    // node和n1 n2都不一条边上 在第三条边 那肯定不是简单路径了
                    if(f2 != n2 && f2 != node) return false;
                    n2 = f2 == n2 ? node : n2; // node和n2在同一条边上 边的端点要延伸至更下方的点
                }
            } else n1 = f1 == n1 ? node : n1; // node和n1在同一条边上 边的端点要延伸至更下方的点
        }
    }
    if(n1 == -1 || n2 == -1) return true; // 只找到最多一条边的情况
    // 有两条边 那么必须要求这两边的lca必须就是root 否则他们是根下面一条路径的两个分枝 就不是单一路径了
    return lca(n1, n2) == root;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs1(1, -1), lca(1);
    cin >> q;
    while(q-- > 0) {
        cin >> m;
        cout << (check() ? "YES" : "NO") << "\n";
    }
};