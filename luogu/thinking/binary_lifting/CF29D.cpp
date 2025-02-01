/**
 * @Time : 2025/1/31-4:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF29D 2000 倍增 lca 模拟
 */
 /*
  * 按顺序访问结点 其实就是从根1到第一个n1
  * 然后到n1和n2的最近公共祖先t1 = lca(n1, n2)，然后从t1到n2
  * 然后从n2到t2 = lca(n2, n3), 然后从t2到n3....
  * 用倍增找lca，然后就是按题意模拟 实现题目要求
  * 注意判断走过的结点数目不能超过2n-1即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 300 + 5, M = 2 * N;
int n, total = 0, depth[N], nodes[N], nxt[N];
vector<int> graph[N], ans;
vector<vector<int>> f;

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

void init() {
    f = vector(n + 1, vector(31, -1)); // 必须初始值为-1
    function<void(int, int)> dfs = [&](int v, int father) {
        if(father != -1) {
            depth[v] = depth[father] + 1;
            nxt[v] = father; // 建反图
            if(graph[v].size() == 1) total++; // 叶子结点
        }
        f[v][0] = father;
        for(int j = 1; j < 31 && f[v][j - 1] != -1; j++)
            f[v][j] = f[f[v][j - 1]][j - 1];
        for(int w : graph[v]) {
            if(w != father)
                dfs(w, v);
        }
    };
    dfs(1, -1);
}

void add_path(int start, int end, bool flag) {
    vector<int> path;
    if(flag) path.push_back(start);
    for(int v = start; v != end; ) {
        v = nxt[v];
        path.push_back(v);
    }
    if(!flag) path.pop_back();
    if(flag) reverse(path.begin(), path.end());
    for(int num : path)
        ans.push_back(num);
}

void solve() {
    init();
    for(int i = 1; i <= total; i++)
        cin >> nodes[i];
    add_path(nodes[1], 1, true);
    for(int i = 1; i < total && ans.size() <= 2 * n + 1; i++) {
        int t = lca(nodes[i], nodes[i + 1]);
        add_path(nodes[i], t, false);
        add_path(nodes[i + 1], t, true);
    }
    add_path(nodes[total], 1, false);
    ans.push_back(1);
    if(ans.size() != 2 * n - 1) {
        cout << -1;
    } else {
        for(int num : ans)
            cout << num << " ";
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
};