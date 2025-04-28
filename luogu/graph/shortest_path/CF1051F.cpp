/**
 * @Time : 2025/4/27-5:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1051F 2400 图论 dijkstra lca 并查集 暴力枚举
 */
/*
  * 注意到 m - n <= 20，边的数量仅比结点多一点点
  * 在完整构建一棵树的情况下，最多多20条边
  * 考虑(u, v)的最短路径
  * 1.有可能是走的树的路径，那么使用lca可以解决
  * 2.有可能会走构建完树之外的多的路径，将这些路径上的两个点叫特殊点t
  * 最短路径经过这些路径，那么必然讲过了特殊点t
  * u->t, t->v，枚举u到v经过的所有特殊点 取其中最小的
  * 因为特殊点比较有限 所以可以针对特殊点都跑dijkstra，这样就能计算 dis(u,t) dis(v,t)
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, mod = 998244353;
int T, n, m, q, depth[N], f[N][32], queries[N][2], marked[N];
ll treeDis[N][32], ans[N], distTo[N];
vector<vector<int>> edges;
vector<vector<int>> graph[N];

// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        ll t = distTo[a[0]] + a[2] - distTo[b[0]] - b[2];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int s) {
    fill(marked, marked + n + 1, 0), fill(distTo, distTo + n + 1, LONG_LONG_MAX);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    distTo[s] = 0;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for (auto &edge: graph[v]) {
            int w = edge[1], weight = edge[2];
            if (distTo[w] > distTo[v] + weight) {
                distTo[w] = distTo[v] + weight;
                pq.push(edge);
            }
        }
    };
    relax(s);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

void path_addition(int s) {
    dijkstra(s);
    for(int i = 1; i <= q; i++) {
        int v = queries[i][0], w = queries[i][1];
        ans[i] = min(distTo[v] + distTo[w], ans[i]);
    }
}

void dfs(int v, int father, int d) {
    if(father != -1) depth[v] = depth[father] + 1;
    f[v][0] = father, treeDis[v][0] = d;
    for(int j = 1; j < 31 && f[v][j - 1] != -1; j++) {
        f[v][j] = f[f[v][j - 1]][j - 1];
        treeDis[v][j] = treeDis[v][j - 1] + treeDis[f[v][j - 1]][j - 1];
    }
    for(auto& edge : graph[v]) {
        if(edge[1] != father)
            dfs(edge[1], v, edge[2]);
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

ll get_path_sum(int v, int father) {
    int k = depth[v] - depth[father];
    ll ans = 0;
    for(int j = 0; j < 31; j++) {
        if((1 << j) & k) {
            ans += treeDis[v][j];
            v = f[v][j];
        }
    }
    return ans;
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

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

void solve() {
    // 走构建的树上的最短路
    memset(f, -1, sizeof(f));
    dfs(1, -1, 0);
    for(int i = 1; i <= q; i++) {
        int v = queries[i][0], w = queries[i][1], comm = lca(v, w);
        ll d1 = get_path_sum(v, comm), d2 = get_path_sum(w, comm);
        ans[i] = d1 + d2;
    }
    // 将图补全 考虑走额外的边的特殊点
    for(auto& edge : edges) {
        int a = edge[0], b = edge[1], d = edge[2];
        graph[a].push_back({a, b, d}), graph[b].push_back({b, a, d});
    }
    for(auto& edge : edges) {
        int a = edge[0], b = edge[1];
        path_addition(a), path_addition(b);
    }
    for(int i = 1; i <= q; i++)
        cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    UF uf(n + 1);
    for(int i = 1, a, b, d; i <= m; i++) {
        cin >> a >> b >> d;
        bool flag = uf.connect(a, b);
        if(!flag) graph[a].push_back({a, b, d}), graph[b].push_back({b, a, d});
        else edges.push_back({a, b, d});
    }
    cin >> q;
    for(int i = 1; i <= q; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }
    solve();
}