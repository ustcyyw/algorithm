/**
 * @Time : 2024/12/17-9:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1805D 1800 图论 树的直径 lca 离线思路
 */
 /*
  * 结论：树中任意一个顶点到另外一个顶点的最远距离是到直径到两个端点之一
  * 所以在给定k的时候 任意一点v和另外一点w如果可以连通
  * 那么dis(v,w) >= k, 那么一定有
  * dis(v,a) >= k or dis(v,b) >= k
  * 并且dis(w,a) >= k or dis(w,b) >= k
  * 也就是说v一定和a或者b连通，w也一定和a或者b连通
  * 再根据直径的定义 dis(a,b) >= k，a和b也连通 因此v w a b在一个连通分量
  * 所以考虑点与点之间的连通时，只需要考虑点与直径端点的距离 >= k，就与直径端点连通
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int T, n, d = 0, a, b, depth[N], f[N][32], degree[N];
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
    dfs1(1, -1), dfs2(a, -1);
    // 计算各个结点和两个端点的距离 注意深度是根据端点a来计算的
    vector<int> arr;
    for(int i = 1; i <= n; i++) {
        int v = lca(b, i);
        int d1 = depth[i], d2 = depth[b] + d1 - 2 * depth[v];
        arr.push_back(max(d1, d2));
    }
    sort(arr.begin(), arr.end());
    vector<int> ans;
    for(int i = n - 1, k = n; k >= 1; k--) {
        while(arr[i] >= k && i >= 0) i--;
        int cnt = n - 1 - i;
        ans.push_back(cnt == 0 ? n : n - cnt + 1);
    }
    for(int i = n - 1; i >= 0; i--)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
            degree[v]++, degree[w]++;
        }
        solve();
    }
};