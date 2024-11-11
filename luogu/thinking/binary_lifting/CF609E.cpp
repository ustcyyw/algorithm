/**
 * @Time : 2024/4/7-9:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 找到最小生成树之后 如果再将强制要求的边连接上
  * 如果该边原本就在最小生成树中 则对答案无影响
  * 但是该边不在最小生成树中 就会形成一个环 要是一个最小生成树
  * 就还得去掉一个边 并且要保持所有结点仍在一个连通分量 那就只能从环中找一条边去掉
  * 于是问题变成了找环上最大的边 可以借用lca倍增的思路来找
  * 因为这个环 除开强制使用的这条边以为 另外的边是树中原本的边
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5, T = 205;
int n, m, marked[N], fw[N], father[N][32], me[N][31], depth[N];
ll base;
vector<vector<int>> edges;
vector<vector<int>> graph[N], tree[N];

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool is_connect(int p, int q) {
        return find(p) == find(q);
    }

    bool connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

void dfs(int v, int f) {
    depth[v] = f == -1 ? 0 : depth[f] + 1;
    father[v][0] = f, me[v][0] = fw[v];
    for(int j = 1; j < 31 && father[v][j - 1] != -1; j++) {
        int w = father[v][j - 1];
        father[v][j] = father[w][j - 1];
        me[v][j] = max(me[v][j - 1], me[w][j - 1]);
    }
    for(auto& edge : graph[v]) {
        if(edge[1] == f) continue;
        fw[edge[1]] = edge[2]; // 记录子结点到父亲的边权重
        dfs(edge[1], v);
    }
}

int getKthAncestor(int node, int k){
    for(int i = 0; i < 31; i++){
        if(((1 << i) & k) > 0)
            node = father[node][i];
    }
    return node;
}

int lca(int x, int y){
    if(depth[x] > depth[y]) swap(x, y); // 保证w更深
    y = getKthAncestor(y, depth[y] - depth[x]); // 保证x和y同一深度
    if(x == y) return y;
    // 找到第一个不是它们祖先的两个点。
    for (int j = 30; j >= 0 && y != x; --j) {
        if (father[x][j] != father[y][j])
            x = father[x][j], y = father[y][j];
    }
    return father[x][0];
}
// 某个结点到祖先结点f的路径上的最大权重
int path(int v, int f) {
    int ans = 0;
    for(int i = 0, k = depth[v] - depth[f]; i < 31; i++){
        if(((1 << i) & k) > 0) {
            ans = max(ans, me[v][i]);
            v = father[v][i];
        }
    }
    return ans;
}

// 查找v-w这条边连接后 对应环上除了这条边以外的最大边权
int search(int v, int w) {
    int f = lca(v, w);
    return max(path(v, f), path(w, f));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        edges.push_back({a, b, w, i});
    }
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) -> bool {return a[2] < b[2];});
    UF uf(n);
    base = 0;
    for(auto& edge : edges) {
        int p = edge[0], q = edge[1], w = edge[2];
        if(!uf.connect(p, q)) {
            base += w, marked[edge[3]] = true;
            graph[p].push_back({p, q, w}), graph[q].push_back({q, p, w});
        }
    }
    dfs(1, -1);
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) -> bool {return a[3] < b[3];});
    for(auto& edge : edges) {
        int p = edge[0], q = edge[1], w = edge[2];
        ll ans = marked[edge[3]] ? base : base + w - search(p, q);
        cout << ans << "\n";
    }
};