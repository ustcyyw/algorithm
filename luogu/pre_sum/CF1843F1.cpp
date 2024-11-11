/**
 * @Time : 2024/9/10-4:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1843F1 前缀和 dfs
 */
 /*
  * 因为结点的值是1和-1 路径上结点和一定是连续变化的
  * 只要找到(u,v)上子路径的最大值和最小值 就能确定所有路径的值的范围
  * 再查看k是否在这个范围即可
  *
  * 前缀和的思想来计算最大子段和
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, val[N], cn, v1[N], v2[N];
char type;
vector<vector<int>> queries, graph;

void dfs(int v, int f, int sum, int preMin, int preMax) {
    sum += val[v];
    preMax = max(preMax, sum), preMin = min(preMin, sum);
    v1[v] = min(v1[f], sum - preMax), v2[v] = max(v2[f], sum - preMin);
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v, sum, preMin, preMax);
    }
}

bool check(int u, int v, int k) {
    if(v == 1) return k == 1 || k == 0;
    return v1[v] <= k && k <= v2[v];
}

void solve() {
    v1[0] = INT_MAX, v2[0] = INT_MIN;
    dfs(1, 0, 0, 0, 0);
    for(auto& query : queries) {
        cout << (check(query[0], query[1], query[2]) ? "YES" : "NO") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        val[1] = 1, cn = 1, queries = {}, graph.assign(n + 2, {});
        for(int i = 1, u, v, k, x; i <= n; i++) {
            cin >> type;
            if(type == '+') {
                cin >> v >> x;
                cn++;
                val[cn] = x;
                graph[cn].push_back(v), graph[v].push_back(cn);
            } else {
                cin >> u >> v >> k;
                queries.push_back({u, v, k});
            }
        }
        solve();
    }
};