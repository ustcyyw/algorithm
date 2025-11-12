/**
 * @Time : 2024/9/22-11:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1878G lca 倍增 暴力枚举 二分
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353, M = 18;
// val[i][j]: i为起点向上路径长度2^j的所有结点位或和
int T, n, q, nums[N], father[N][M], val[N][M], depth[N];
vector<vector<int>> graph; // 多测试用例 father数组必须每次重制

void dfs(int v, int f) {
    depth[v] = f == -1 ? 0 : depth[f] + 1;
    father[v][0] = f, val[v][0] = nums[v] | (f == -1 ? 0 : nums[f]);
    for(int j = 1; j < M && father[v][j - 1] != -1; j++) {
        int w = father[v][j - 1];
        father[v][j] = father[w][j - 1];
        val[v][j] = val[v][j - 1] | val[w][j - 1];
    }
    for(int w : graph[v]) {
        if(w != f)
            dfs(w, v);
    }
}

int getKthAncestor(int node, int k){
    for(int i = 0; i < M; i++){
        if(((1 << i) & k) > 0)
            node = father[node][i];
    }
    return node;
}

// 计算结点node向上路径长度为k的所有结点位或和
int getKthVal(int node, int k) {
    if(k == 0) return nums[node];
    int ans = 0;
    for(int i = 0; i < M; i++){
        if(((1 << i) & k) > 0) {
            ans |= val[node][i];
            node = father[node][i];
        }
    }
    return ans;
}

int lca(int x, int y){
    if(depth[x] > depth[y]) swap(x, y); // 保证w更深
    y = getKthAncestor(y, depth[y] - depth[x]); // 保证x和y同一深度
    if(x == y) return y;
    // 找到第一个不是它们祖先的两个点。
    for (int j = M - 1; j >= 0 && y != x; --j) {
        if (father[x][j] != father[y][j])
            x = father[x][j], y = father[y][j];
    }
    return father[x][0];
}

// 枚举x这个结点这一侧的路径产生的1的个数 计算最大值
int cal(int x, int y, int f) {
    int ans = 0;
    for(int cnt = __builtin_popcount(nums[x]); cnt <= 30; cnt++) {
        int lo = 0, hi = depth[x] - depth[f] + 1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(__builtin_popcount(getKthVal(x, mid)) >= cnt) hi = mid;
            else lo = mid + 1;
        }
        if(lo == depth[x] - depth[f] + 1) break;
        // 计算答案
        int z = getKthAncestor(x, lo);
        int v1 = getKthVal(z, depth[z] - depth[f]), v2 = getKthVal(y, depth[y] - depth[f]);
        ans = max(ans, cnt + __builtin_popcount(v1 | v2));
    }
    return ans;
}

void solve(int x, int y) {
    int f = lca(x, y);
    cout << max(cal(x, y, f), cal(y, x, f)) << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {});
        for(int i = 1; i <= n; i++)
            fill(father[i], father[i] + M, -1); // 多测试用例 father数组必须每次重制 初值为-1
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1);
        cin >> q;
        for(int i = 1, x, y; i <= q; i++) {
            cin >> x >> y;
            solve(x, y);
        }
        cout << "\n";
    };
};